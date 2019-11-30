//
//  main.cpp
//  Algorithm_HW1
//
//  Created by 蕭弈均 on 2019/11/27.
//  Copyright © 2019 蕭弈均. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <vector>
using namespace std;

//function
int findK(int j,vector<vector<int> >& input)
{
    int k=0;
    for(int index=0;index<input.size();index++)
    {
        if(input[index][0]==j)
        {
            k=input[index][1];
            break;
        }
        
         if(input[index][1]==j)
         {
             k=input[index][0];
             break;
         }
            
    }
    return k;
}
int a=0;
void findChord(int i, int j, vector<vector<int> >& chord, vector<vector<int> >& checkcase, vector<vector<int> >&  Sol,vector<vector<int> >& MIS)
{
    {
        if(checkcase[i][j]==1)
        {
            findChord(i,j-1,chord,checkcase,Sol,MIS);
        }
        if(checkcase[i][j]==2)
        {
            
         if( MIS[i][j-1]>MIS[i][findK(j, chord)-1]+1+MIS[findK(j, chord)+1][j-1] )
            {
                findChord(i, j-1, chord, checkcase, Sol,MIS);
            }
            else
            {
                Sol[a][0]=findK(j, chord);
                Sol[a][1]=j;
                a++;
                findChord(i, findK(j, chord), chord, checkcase, Sol,MIS);
                findChord(findK(j, chord)+1, j-1, chord, checkcase, Sol,MIS);
                
            }
        }
        if(checkcase[i][j]==3)
        {
            Sol[a][0]=i;
            Sol[a][1]=j;
            a++;
            findChord(i+1,j-1, chord, checkcase, Sol,MIS);
            
        }
            
        
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    //int A[100][100];
    
    if(argc != 3)
    {
        cout << "Usage: ./[exe] [input file] [output file]" << endl;
    //    system("pause");
        exit(1);
    }

    // open the input file
    fstream fin;
    fin.open(argv[1], fstream::in);
    if(!fin.is_open())
    {
        cout << "Error: the input file is not opened!!" << endl;
        exit(1);
    }

    // parse the input file
    cout << "======================" << endl;
    cout << "        Parser        " << endl;
    cout << "======================" << endl;

    char buffer[10000];
    fin >> buffer;
    int numChord = atoi(buffer);
    int N=numChord/2;
    
    vector< vector<int> > chord;
    chord.resize(N);
    for(int i=0;i<N;++i)
    {
        chord[i].resize(2);
    }
    //
    //create MIS(i,j)=[numChord][numChord]
    vector< vector<int> > MIS;
    MIS.resize(numChord);
    for(int i=0;i<numChord;++i)
    {
        MIS[i].resize(numChord);
    }
    for(int i=0;i<numChord;++i)
    {
        for(int j=0;j<numChord;++j)
        {
                MIS[i][j]=0;
        }
    }
    //create checkcase(i,j)=[numChord][numChord]
    vector< vector<int> > checkcase;
    checkcase.resize(numChord);
    for(int i=0;i<numChord;++i)
    {
        checkcase[i].resize(numChord);
    }
    for(int i=0;i<numChord;++i)
    {
        for(int j=0;j<numChord;++j)
        {
            checkcase[i][j]=0;
        }
    }
    //
    //create SolLine(i,j)=[N][2]
    vector< vector<int> > SolLine;
    SolLine.resize(N);
    for(int i=0;i<N;++i)
    {
        SolLine[i].resize(2);
    }
    for(int i=0;i<N;++i)
    {
        for(int j=0;j<2;++j)
        {
            SolLine[i][j]=0;
        }
    }
    
    //
    
    cout << "#Chords:" << numChord << endl;

    for(int i = 0; i < numChord / 2; ++i)
    {
        fin >> buffer;
        int point1 = atoi(buffer);
        chord[i][0]=point1;
        fin >> buffer;
        int point2 = atoi(buffer);
        chord[i][1]=point2;
        cout << "Chord(" << point1 << "," << point2 << ")" << endl;
    }
    //
   
    
    int k=0;
    // find the MIS(i,j)
    for(int j=0;j<=2*N-1;++j)
    {
        // k=the number such that kj,jk belongs to C
        k=findK(j,chord);
        //-------------------------------
        for(int i=0;i<=j-1;++i)
        {
            //case 3
            if ( i==k )
               {MIS[i][j]=MIS[i+1][j-1]+1;
                checkcase[i][j]=3;
               }
            //case 2
            else if (i<k && k<=(j-1) )
            {
                if( MIS[i][j-1]>MIS[i][k-1]+1+MIS[k+1][j-1] )
                    MIS[i][j]=MIS[i][j-1];
                else
                    MIS[i][j]=MIS[i][k-1]+1+MIS[k+1][j-1];
            checkcase[i][j]=2;
            }
            //caes 1
            if (k<i || k>j)
            {  MIS[i][j]=MIS[i][j-1];
               checkcase[i][j]=1;
            }
        }
    }
    //find the solution of chord
    findChord(0, 2*N-1, chord, checkcase, SolLine,MIS);

    // open the output file
    fstream fout;
    fout.open(argv[2],fstream::out);
    if(!fout.is_open())
    {
        cout << "Error: the output file is not opened!!" << endl;
        exit(1);
    }

    // output something to the output file
    fout<<MIS[0][2*N-1]<<endl;
    int solNum=MIS[0][2*N-1];
    for(int i=0;i<solNum;++i)
    {
       fout <<SolLine[i][0] <<" "<< SolLine[i][1]<<endl;
    }
    //fout<<MIS[0][2*N-1]<<endl;
    //fout<<k<<endl;
    //delete [] vertex;
    return 0;
}

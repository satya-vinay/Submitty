/*Copyright (c) 2014, Chris Berger, Jesse Freitas, Severin Ibarluzea,
 Kiana McNellis, Kienan Knight-Boehm
 
 All rights reserved.
 This code is licensed using the BSD "3-Clause" license. Please refer to
 "LICENSE.md" for the full license
 */


#ifndef differences_myersDiff_h
#define differences_myersDiff_h


#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <cctype>
#include <fstream>
#include <algorithm>

//using std::cout; using std::endl; using std::cin; using std::string; using std::vector;
//pass chunks of text in strings
// return int did it work?
// diff_naive() - character by character
// diff_line()
// diff_no_whitespace()
// empty() - checks if blank student strings
// not_empty() -checks if student string has content
// edit_distance_naive()
// edit distance_line()
typedef unsigned int size_type;
size_type SES(const std::string & A, const std::string & B){
    size_type N=(size_type)A.size();
    size_type M=(size_type)B.size();
    std::vector<int> V((N+M)*2,0);
    std::vector< std::vector<int> > Snakes;
    for (int a=0; a<(N+M)+(N+M); a++) {
        V[a]=0;
    }
    for ( int d = 0 ; d <= N + M ; d++ ){
        for ( int k = -d ; k <= d ; k += 2 ){
            bool down = (k==-d || (k!=d && V[(k-1)+(N+M)] < V[(k+1)+(N+M)]));
            //std::cout<<k<<" "<<V[(k)+(N+M)]<<std::endl;
            int kPrev, xStart, yStart, xEnd, yEnd;
            if (down) {
                kPrev=k+1;
                xStart = V[kPrev+(N+M)];
                xEnd=xStart;
            }
            else
            {
                kPrev=k-1;
                xStart = V[kPrev+(N+M)];
                xEnd=xStart + 1;
            }
            yStart = xStart - kPrev;
            yEnd = xEnd - k;
            // follow diagonal
            int snake = 0;
            while ( xEnd < N && yEnd < M && A[xEnd] == B[yEnd] ){
                xEnd++; yEnd++; snake++;
            }
            
            // save end point
            V[ k +(N+M)] = xEnd;
            Snakes.push_back(V);
            // check for solution
            if ( xEnd >= N && yEnd >= M ){ /* solution has been found */
                return d;
            }
        }
        
    }
    
    return -1;
}



#endif
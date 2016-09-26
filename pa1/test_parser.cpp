/*************************************************************
 * File Name : test_parser.cpp
 * Purpose : For test parser provided by TA
 * Creation Date : Thu 22 Sep 2016 06:44:06 PM CST
 * Last Modified : Fri 23 Sep 2016 11:16:41 AM CST
 * Created By : SL Chung
 **************************************************************/
#include <cstdio>
#include <iostream>
#include "parser.h"
int main( int argc, char** argv )
{
    // Declare the functional objects
    AlgParser p;
    AlgTimer t;
    // Pass the arguement 1 as the input file name
    p.Parse( argv[1] );
    // Start timer
    t.Begin();
    // Display all strings and word numbers
    for( int i = 0 ; i < p.QueryTotalStringCount() ; i++ )
    {
        cout << p.QueryString(i) << " " << p.QueryLineNumber(i) << "  " << p. QueryWordOrder(i) << endl;
    }
    // Display the accumulated time
    cout << "The execution spends " << t.End() << " seconds" << endl;
    return 0;
} 

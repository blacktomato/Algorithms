/*************************************************************
 * File Name : sort.cpp
 * Purpose : Sort the word data
 * Creation Date : Fri 23 Sep 2016 11:50:07 AM CST
 * Last Modified : Fri 23 Sep 2016 06:03:41 PM CST
 * Created By : SL Chung
**************************************************************/
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"parser.h"

using namespace std;

typedef pair<string,int> data;

void print_data(const vector<data>&);
void swap(data&, data&);

int main(int argc, char** argv)
{

    AlgParser p;
    AlgTimer t;
    
    p.Parse(argv[1]);
    //total word count
    int Total = p.QueryTotalStringCount();
    cout << Total << "\n";

    //the data set
    vector<data> d;
    for(int i = 0; i < Total; i++)
    {
        pair< string, int > word(p.QueryString(i), i);
        d.push_back(word);
    }
    
    //for different sorting method
    string option = argv[2];
    if (option == "-insert")
    {
        for(int i = 1; i < Total; i++)
        {
            int j = i;
            while(d[j] < d[j-1])
            {
                swap(d[j], d[j-1]);
                if (j > 1) j--;
            }
        }
    }
    else if (option == "-merge");
    else if (option == "-heap");
    else if (option == "-quick");
    
    //show the output
    print_data(d);
    return 0;
}

void print_data(const vector<data> &Data)
{
    for(size_t i = 0; i < Data.size(); i++)
    {
        cout << Data[i].first << " " << Data[i].second << "\n";
    }
}

void swap(data &a, data &b)
{
    data temp = a;
    a = b;
    b = temp;
}

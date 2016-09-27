/*************************************************************
 * File Name : sort.cpp
 * Purpose : Sort the word data
 * Creation Date : Fri 23 Sep 2016 11:50:07 AM CST
 * Last Modified : Tue 27 Sep 2016 09:21:22 PM CST
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
void mergesort(vector<data>&);
void quicksort(vector<data>&);


int main(int argc, char** argv)
{

    AlgParser p;
    AlgTimer t;
    
    p.Parse(argv[1]);
    //total word count
    int Total = p.QueryTotalStringCount();
    cout << Total << "\n";

    //create the data set
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
    else if (option == "-merge")
    {
        mergesort(d);
    }
    else if (option == "-heap")
    {
        ;
    }
    else if (option == "-quick")
    {
        
    }   
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

void mergesort(vector<data> &datas)
{
    size_t s =  datas.size();
    size_t count = 0;
    if (s == 1 || s == 0);
    else if (s >= 2)
    {
        vector<data> temp1(datas.begin(), datas.end() - s / 2);
        size_t n = s / 2;
        if (s % 2 == 0); else n++;
        vector<data> temp2(datas.begin() + n, datas.end());
        mergesort(temp1);
        mergesort(temp2);
        vector<data> temp;
        while(temp1.size() * temp2.size() != 0)
        {
            if (temp1[0] <= temp2[0])
            {
                temp.push_back(temp1[0]);
                temp1.erase(temp1.begin());
            }
            else
            {
                temp.push_back(temp2[0]);
                temp2.erase(temp2.begin());
            }
            count++;
        }
        while(count != s)
        {
            if (temp1.size() != 0)
            {
                temp.push_back(temp1[0]);
                temp1.erase(temp1.begin());
            }
            else if (temp2.size() != 0)
            {
                temp.push_back(temp2[0]);
                temp2.erase(temp2.begin());
            }
            count++;
        }

        datas = temp;
    }   
}       

void quicksort(vector<data> &datas)
{
    size_t s =  datas.size();
    if (s == 1 || s == 0);
    else if (s >= 2)
    {
        bool done = false;
        vector<data>::iterator it = datas.begin();
        vector<data>::iterator comp = datas.end() - 1;
        while(!done)
        {
            if(it < comp)
            {   
                if ( (*it).first <= (*comp).first)
                    comp--;
                else
                {
                    swap(*it, *comp);
                    vector<data>::iterator temp;
                    temp = it;
                    it = comp;
                    comp = temp;
                    comp++;
                }
            }
            else if (it > comp)
            {
                if ( (*it).first >= (*comp).first)
                    comp++;
                else
                {
                    swap(*it, *comp);
                    vector<data>::iterator temp;
                    temp = it;
                    it = comp;
                    comp = temp;
                    comp--;
                }
            }
            else break;
        }
        vector<data> &sub1(datas.begin(), it);
        vector<data> &sub2(++it, datas.end());
    }   
}       

/*************************************************************
 * File Name : sort.cpp
 * Purpose : Sort the word data
 * Creation Date : Fri 23 Sep 2016 11:50:07 AM CST
 * Last Modified : Wed 28 Sep 2016 10:54:44 PM CST
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
void quicksort(vector<data>&, int, int);
void heapify(vector<data>&, size_t, size_t);
void heapsort(vector<data>&);

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
        heapsort(d);
    }
    else if (option == "-quick")
    {
       quicksort(d, 0, Total - 1); 
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

void heapify(vector<data> &datas, size_t root, size_t length)
{
    size_t leftNode = root * 2 + 1;
    size_t rightNode = root * 2 + 2;
    //default setting the maxNode is root
    size_t maxNode = root;
    if (leftNode < length && datas[leftNode].first > datas[maxNode].first)
        maxNode = leftNode;
    if (rightNode < length && datas[rightNode].first > datas[maxNode].first)
        maxNode = rightNode;
    if (maxNode != root)
    {
        swap(datas[maxNode], datas[root]);
        heapify(datas, maxNode, length);
    }
}

void heapsort(vector<data> &datas)
{
    size_t length = datas.size();
    for (int i = length / 2 - 1; i >= 0; i--)
    {
        heapify(datas, i, length);
    }
    for (size_t i = length - 1; i > 0; i--)
    {
        swap(datas[i], datas[0]);
        heapify(datas, 0, i);
    }
}

void quicksort(vector<data> &datas, int start, int end)
{
    int s =  end - start + 1;
    if (s == 1 || s == 0);
    else if (s >= 2)
    {
        int iter = start;
        int comp = end;
        bool done = false;
        while(!done)
        {
            if(iter < comp)
            {   
                if ( datas[iter].first <= datas[comp].first)
                    comp--;
                else
                {
                    swap(datas[iter], datas[comp]);
                    int temp;
                    temp = iter;
                    iter = comp;
                    comp = temp;
                    comp++;
                }
            }
            else if (iter > comp)
            {
                if ( datas[iter].first >= datas[comp].first)
                    comp++;
                else
                {
                    swap(datas[iter], datas[comp]);
                    int temp;
                    temp = iter;
                    iter = comp;
                    comp = temp;
                    comp--;
                }
            }
            else break;
        }
        quicksort(datas, start, iter - 1);
        quicksort(datas, iter + 1, end);
    }   
}       

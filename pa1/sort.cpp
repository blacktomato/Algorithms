/*************************************************************
 * File Name : sort.cpp
 * Purpose : Sort the word data
 * Creation Date : Fri 23 Sep 2016 11:50:07 AM CST
 * Last Modified : Sat 01 Oct 2016 23:37:32 CST
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
void mergesort(vector<data>&, size_t, size_t);
void quicksort(vector<data>&, size_t, size_t);
void heapify(vector<data>&, size_t, size_t);
void heapsort(vector<data>&);
void output(vector<data>&, string&);

int main(int argc, char** argv)
{

    AlgParser p;
    AlgTimer t;
    if (argc < 4)
    {
        cerr << "Error: The command format should be "
             << "\"./sort <input-file> <sort-option> <output-file>\"" << endl;
        return 1;
    }

    p.Parse(argv[1]);
    //total word count
    int Total = p.QueryTotalStringCount();
    
    //start the timer
    t.Begin();

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
        for(int i = 0; i < Total - 1; i++)
        {
            //cout << i << endl;
            int j = i;
            data temp = d[j + 1];
            while(temp.first < d[j].first)
            {
                d[j + 1] = d[j];
                if (j > 0) j--;
                else if(j == 0) break;
            }
            d[j] = temp;
         }
    } 
    else if (option == "-merge")
    {
        mergesort(d, 0, Total);
    }
    else if (option == "-heap")
    {
        heapsort(d);
    }
    else if (option == "-quick")
    {
       quicksort(d, 0, Total - 1); 
    }
    else
    {
        cerr << "Error: Need to choose a sorting algorithm: -insert|-merge|-heap|-quick" << endl;
        return 1;
    }
    //show the output
    //print_data(d);

    //write into the file
    string filename = argv[3];
    output(d, filename);
    
    cout << "The execution spends " << t.End() << " seconds" << endl;
    cout << "Press Enter to terminate the program..." << endl;
    getchar();
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

void mergesort(vector<data> &datas, size_t start, size_t end)
{
    size_t s =  end - start;    //start from 0
    size_t count = 0;
    if (s == 1 || s == 0);
    else if (s >= 2)
    {
        size_t start_1 = start;
        size_t end_1 = end - s / 2;
        size_t start_2 = end_1;
        size_t end_2 = end;
        mergesort(datas, start_1, end_1);
        mergesort(datas, start_2, end_2);
        vector<data> temp;
        while((end_1 - start_1) * (end_2 - start_2) != 0)
        {
            if (datas[start_1] <= datas[start_2])
            {
                temp.push_back(datas[start_1]);
                start_1++;
            }
            else
            {
                temp.push_back(datas[start_2]);
                start_2++;
            }
            count++;
        }
        while(count != s)
        {
            if (end_1 - start_1 != 0)
            {
                temp.push_back(datas[start_1]);
                start_1++;
            }
            else if (end_2 - start_2 != 0)
            {
                temp.push_back(datas[start_2]);
                start_2++;
            }
            count++;
        }
        for(size_t i = start; i < end; i++)
        {
            datas[i] = temp[i - start];
        }
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

void quicksort(vector<data> &datas, size_t start, size_t end)
{
    size_t s =  end - start + 1;
    if (s == 1 || s == 0);
    else if (s >= 2)
    {
        size_t iter = start;
        size_t comp = end;
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

void output(vector<data>& datas, string& file_name)
{
    fstream file;
    file.open(file_name.c_str(), fstream::out);
    file << datas.size() << "\n";
    if (file.is_open())
    {
        for (size_t i = 0; i < datas.size(); i++)
        {
            file << datas[i].first << " " << datas[i].second << "\n";
        }
    }
    else cerr << "Fail to open the file \"" << file_name << "\"\n";
    file.close();
}

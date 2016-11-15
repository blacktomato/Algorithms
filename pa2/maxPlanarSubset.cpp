/*************************************************************
 * File Name : maxPlanarSubset.cpp
 * Purpose : Count the max planar subset with numbers of vertices on a circle
 * Creation Date : Tue 15 Nov 2016 12:19:28 PM CST
 * Last Modified : Wed 16 Nov 2016 01:22:58 AM CST
 * Created By : SL Chung
**************************************************************/
#include<cstdio>
#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;
typedef pair<int, int> line;

void mergesort(vector<line>&, int, int);
int max_finder(int, int, int**, vector<line>&);

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        cerr << "Error: The command format should be "
             << "\"./maxPSubset <input-file.in> <output-file>\"" << endl;
        return 1;
    }

    ifstream infile;
    infile.open(argv[1], ios::in);
    if(!infile)
    {
        cerr << "input-file: " << argv[1] << " can't open!";
        return 1;
    }

    //reading file
    int vertice_number = 0;
    int line_number = 0;
    vector<line> line_set;
    infile >> vertice_number;
    line_number = vertice_number / 2
    for(int i = 0; i < line_number; i++)
    {
        int v1, v2;
        infile >> v1;
        infile >> v2;
        if (v1 <= v2)
        {
            line l(v1, v2);
            line_set.push_back(l);
        }
        else
        {
            line l(v2, v1);
            line_set.push_back(l);
        }
    }

    // sorting the lines by the start(first)
    mergesort(line_set, 0, line_number);

    int **maxPTable = new int *[vertice_number];
    for (int k = 0; k < vertice_number; k++)
        maxPTable[k] = new int[vertice_number]();
        memset(maxPTable[k], -1, sizeof(int) * vertice_number);
        maxPTable[k][k] = 0;

    for (int len = 1; len < vertice_number; i++)
    {
        for (int i = 0; i < vertice_number; i++)
        {
            if (i+len < vertice_number)
                max_finder(i, i + len, maxPTable, line_set);
        }
    }

    ofstream outfile;
    outfile.open(argv[2], ios::out);

    return 0;
}
void mergesort(vector<line> &lines, int start, int end)
{
    int s =  end - start;    //start from 0
    int count = 0;
    if (s == 1 || s == 0);
    else if (s >= 2)
    {
        int start_1 = start;
        int end_1 = end - s / 2;
        int start_2 = end_1;
        int end_2 = end;
        mergesort(lines, start_1, end_1);
        mergesort(lines, start_2, end_2);
        vector<line> temp;
        while((end_1 - start_1) * (end_2 - start_2) != 0)
        {
            if (lines[start_1] <= lines[start_2])
            {
                temp.push_back(lines[start_1]);
                start_1++;
            }
            else
            {
                temp.push_back(lines[start_2]);
                start_2++;
            }
            count++;
        }
        while(count != s)
        {
            if (end_1 - start_1 != 0)
            {
                temp.push_back(lines[start_1]);
                start_1++;
            }
            else if (end_2 - start_2 != 0)
            {
                temp.push_back(lines[start_2]);
                start_2++;
            }
            count++;
        }
        for(int i = start; i < end; i++)
        {
            lines[i] = temp[i - start];
        }
    }   
}        

int max_finder(int start, int end, int **table, vector<line> &line_set)
{
    
}

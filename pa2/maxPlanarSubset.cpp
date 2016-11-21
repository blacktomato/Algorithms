/*************************************************************
 * File Name : maxPlanarSubset.cpp
 * Purpose : Count the max planar subset with numbers of vertices on a circle
 * Creation Date : Tue 15 Nov 2016 12:19:28 PM CST
 * Last Modified : Mon 21 Nov 2016 05:25:34 PM CST
 * Created By : SL Chung
**************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<iomanip>
#include<vector>
#include<fstream>

using namespace std;
typedef pair<int, int> line;

int max_finder(int, int, int**, int*, int**);
int link_tracer(int, int, int**, int*, int**, bool*, vector<line>&);
void checkMTable(int**, int);
void mergesort(vector<line>&, int, int);

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
    infile >> vertice_number;
    int *lineTable = new int[vertice_number];
    bool *reverseTable = new bool[vertice_number];
    line_number = vertice_number / 2;
    for(int i = 0; i < line_number; i++)
    {
        int v1;
        int v2;
        infile >> v1;
        infile >> v2;
        lineTable[v1] = v2;
        lineTable[v2] = v1;
        reverseTable[v1] = false;
        reverseTable[v2] = true;
    }


    int **maxPTable = new int *[vertice_number];
    int **linkPTable = new int *[vertice_number];
    for (int k = 0; k < vertice_number; k++)
    {
        maxPTable[k] = new int[vertice_number];
        memset(maxPTable[k], -1, sizeof(int) * vertice_number);
        maxPTable[k][k] = 0;
        linkPTable[k] = new int[vertice_number];
        memset(linkPTable[k], -1, sizeof(int) * vertice_number);
    }
    

    //Fill the max planar table
    for (int len = 1; len < vertice_number; len++)
    {
        for (int i = 0; i < vertice_number; i++)
        {
            if (i+len < vertice_number)
                maxPTable[i][i+len] = max_finder(i, len, maxPTable, lineTable, linkPTable);
        }
    }
//  cout << "Max Planar Table:" << endl;
//  checkMTable(maxPTable , vertice_number);
//  cout << endl << "Linking Planar Table:" << endl;
//  checkMTable(linkPTable , vertice_number);

    vector<line> lineSet;
    link_tracer(0, vertice_number - 1, maxPTable, lineTable, linkPTable, reverseTable, lineSet);

    //sorting
    mergesort(lineSet, 0, maxPTable[0][vertice_number-1]);
    
    
    //output file
    ofstream outfile;
    outfile.open(argv[2], ios::out);

    outfile << maxPTable[0][vertice_number-1] << "\n";
    for(int i = 0; i < maxPTable[0][vertice_number-1]; i++)
        outfile << lineSet[i].first << " " << lineSet[i].second << endl;
    
    outfile.close();

    //return memory
    delete[] lineTable;
    for (int k = 0; k < vertice_number; k++)
    {
        delete[] maxPTable[k];
        delete[] linkPTable[k];
    }
    delete[] maxPTable;
    delete[] linkPTable;

    return 0;
}

int max_finder(int start, int len, int **maxptable, int *line_table, int **linkptable)
{
    int end = start + len;
    if (maxptable[start][end] != -1) return maxptable[start][end];
    int result = 0;
    
    //default setting (Nothing change)
    result = maxptable[start][start+len-1];
    linkptable[start][start+len] = linkptable[start][start+len-1];
    
    int crosser = line_table[start+len]; 
    if (crosser > start + len || crosser < start){}
    else if (crosser == start)
    {
        if ( len == 1) 
        {
            result = 1;
            linkptable[start][start+len] = start;
        }
        else
        {
            if (result < 1 + maxptable[start+1][start+len-1])
            {
                result = 1 + maxptable[start+1][start+len-1];
                linkptable[start][start+len] = start;
            }
        }
    }
    else
    {
        //For crosser is possible to be next to the start+len
        if (start+len-1 < crosser+1)
        {
            if (result < 1 + maxptable[start][crosser-1])
            {
                result = 1 + maxptable[start][crosser-1];
                linkptable[start][start+len] = crosser;
            }
        }
        else if (result < 1 + maxptable[start][crosser-1] + maxptable[crosser+1][start+len-1])
        {
            result = 1 + maxptable[start][crosser-1] + maxptable[crosser+1][start+len-1];
            linkptable[start][start+len] = crosser;
        }
    } 
    
    return result;
}

void checkMTable(int **maxptable , int side)
{
    cout << setw(4)<< "\\" << "  ";
    for (int j = 0; j < side; j++)
        cout << setw(4)<< j << "  ";
    cout << endl;
    for (int i = 0; i < side; i++)
    {
        cout << setw(4)<< i << "  ";
        for (int j = 0; j < side; j++)
            cout << setw(4)<< maxptable[i][j] << "  ";
        cout << endl;
    }
}

int link_tracer(int start, int end, int** maxptable, int *line_table,
                int **linkptable, bool *reversetable, vector<line> &line_set)
{
    if (linkptable[start][end] == -1) return 1;
    int s = linkptable[start][end];
    line separater;
    if( reversetable[s] == true)
        separater = line(line_table[s], s);
    else
        separater = line(s, line_table[s]);
    
    line_set.push_back(separater);
    if (s-1 >= start)
        link_tracer(start, s-1, maxptable, line_table, linkptable, reversetable, line_set);
    if (s+1 < line_table[s]-1)
        link_tracer(s+1, line_table[s]-1, maxptable, line_table, linkptable, reversetable, line_set);
    if (line_table[s]+1 <= end)
        link_tracer(line_table[s]+1, end, maxptable, line_table, linkptable, reversetable, line_set);
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

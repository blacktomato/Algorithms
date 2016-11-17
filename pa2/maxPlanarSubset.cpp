/*************************************************************
 * File Name : maxPlanarSubset.cpp
 * Purpose : Count the max planar subset with numbers of vertices on a circle
 * Creation Date : Tue 15 Nov 2016 12:19:28 PM CST
 * Last Modified : Thu 17 Nov 2016 07:50:00 PM CST
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
int link_tracer(int, int, int**, int*, int**, vector<line>&);
void checkMTable(int**, int);

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
    line_number = vertice_number / 2;
    for(int i = 0; i < line_number; i++)
    {
        int v1;
        int v2;
        infile >> v1;
        infile >> v2;
        lineTable[v1] = v2;
        lineTable[v2] = v1;
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
    //cout << "Max Planar Table:" << endl;
    //checkMTable(maxPTable , vertice_number);
    //cout << endl << "Linking Planar Table:" << endl;
    //checkMTable(linkPTable , vertice_number);
    
    vector<line> lineSet;
    link_tracer(0, vertice_number - 1, maxPTable, lineTable, linkPTable, lineSet);
    
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
    if(line_table[end] > start && line_table[start] < s)
    for (int i = 0; i <= len; i++)
    {
        if ( i+1 <= len )
        {
            if (result < (maxptable[start][start+i] + maxptable[start+i+1][start+len]))
            {
                result = (maxptable[start][start+i] + maxptable[start+i+1][start+len]);
                if (linkptable[start][start+i] != -1)
                        linkptable[start][start+len] = linkptable[start][start+i];
                else    linkptable[start][start+len] = linkptable[start+i+1][start+len];
            }
        }
        else
        {
            if (line_table[start] == start+len)
            {
                if ( len >= 2 )
                {
                    if (result <= (maxptable[start+1][start + len-1]))
                    {
                        result = 1 + maxptable[start+1][start + len - 1];
                        linkptable[start][start+len] = start;
                    }
                }
                else 
                {
                    result = 1;
                    linkptable[start][start + len] = start;
                }
            }
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

int link_tracer(int start, int end, int** maxptable, int *line_table, int **linkptable, vector<line> &line_set)
{
    if (linkptable[start][end] == -1) return 1;
    int s = linkptable[start][end];
    line separater(s, line_table[s]);
    line_set.push_back(separater);
    if (s-1 >= start)
        link_tracer(start, s-1, maxptable, line_table, linkptable, line_set);
    if (s+1 < line_table[s]-1)
        link_tracer(s+1, line_table[s]-1, maxptable, line_table, linkptable, line_set);
    if (line_table[s]+1 <= end)
        link_tracer(line_table[s]+1, end, maxptable, line_table, linkptable, line_set);
    return 0;
}


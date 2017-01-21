/*************************************************************
 * File Name : router.cpp
 * Purpose : For global routing problem
 * Creation Date : Thu 22 Dec 2016 09:23:51 PM CST
 * Last Modified : Sat 21 Jan 2017 01:40:51 PM CST
 * Created By : SL Chung
**************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <float.h>
#include "parser.h"
#include "graph.h"

using namespace std;

int pair2index(pair<int, int>, int);
pair<int, int> index2pair(int, int);
void swap(pair<int, float>*&, pair<int, float>*&);
void heapify(vector< pair<int, float>* >&, size_t, size_t);
bool comp_sort(pair<int, float> a, pair<int, float> b){return (a.second < b.second);}

int main(int argc, char **argv)
{
    if( argc != 3 ){ cerr << "Usage: ./router [input_file_name] [output_file_name]" << endl; return 1; }

    AlgParser parser;

    // read the file in the first argument
    if( ! parser.read( argv[1] ) ) { cerr << "Fail to open file: " << argv[1] << endl; return 1; }

    //sort the Net by their length
    vector<pair<int, float>> nets;
    for (int idNet = 0; idNet < parser.gNumNets(); idNet++)
    {
        pair<int, int> source = parser.gNetStart( idNet );
        pair<int, int> end = parser.gNetEnd( idNet );
        float length = sqrt(pow(source.first - end.first, 2) + pow(source.second - end.second, 2));
        nets.push_back(make_pair(idNet, length));
    }
    sort(nets.begin(), nets.end(), comp_sort);
    
    //start the timer
    AlgTimer timer;
    Graph RoutingTiles;
    timer.Begin();
    int NumTile = parser.gNumHTiles() * parser.gNumVTiles();
    cout << "building graph...";
    //building a graph from the input_file
    for(int i = 0; i < NumTile; i++)
    {   
        RoutingTiles.add_vertex(i);
    }
    //linking adjacent graph
    for(int i = 0; i < NumTile; i++)
    {   
        pair<int, int> tile = index2pair(i, parser.gNumHTiles());
        if(tile.first - 1 >= 0)
        { 
            tile.first--;
            RoutingTiles.add_link(i, pair2index(tile, parser.gNumHTiles()), parser.gCapacity());
            tile.first++;
        }
        if(tile.first + 1 < parser.gNumHTiles())
        { 
            tile.first++;
            RoutingTiles.add_link(i, pair2index(tile, parser.gNumHTiles()), parser.gCapacity());
            tile.first--;
        }
        if(tile.second - 1 >= 0)
        { 
            tile.second--;
            RoutingTiles.add_link(i, pair2index(tile, parser.gNumHTiles()), parser.gCapacity());
            tile.second++;
        }
        if(tile.second + 1 < parser.gNumVTiles())
        { 
            tile.second++;
            RoutingTiles.add_link(i, pair2index(tile, parser.gNumHTiles()), parser.gCapacity());
            tile.second--;
        }
    }
    cout << "Done" << endl;

    //For Dijkstra's algorithm
    vector<pair<int, float>> WeightTable(NumTile, make_pair(0, 0.0));
    vector<int> TraceTable(NumTile, -1);
    
    //For test
    //RoutingTiles.printGraph();
    
    //gNumNet * each length
    vector<vector< pair<int, int> >> resultTable;

    cout << "Dijkstra Algorithm..." << endl;
    //Do the Dijkstra Algorithm for NumNets times 
    for (int i = 0; i < parser.gNumNets(); ++i)
    {
        int idNet = nets[i].first;
        //cout << "Working the " << idNet << " th net..." << endl;
        vector< pair<int, float>* > ExtractTable(NumTile, 0);
        pair<int, int> source = parser.gNetStart( idNet );
        pair<int, int> end = parser.gNetEnd( idNet );
        int index_s = pair2index(source, parser.gNumHTiles());
        int index_e = pair2index(end, parser.gNumHTiles());
            
        //initialize the tables for each Dijkstra Algorithm
        for(int i = 0; i < NumTile; i++)
        {
            ExtractTable[i] = &WeightTable[i];
            WeightTable[i].first = i;
            WeightTable[i].second = FLT_MAX;
            TraceTable[i] = -1;
        }

        //Initialize Single Source
        WeightTable[index_s].second = 0.0;
        TraceTable[index_s] = index_s;

        //Extract min by using heap to fast the operation
        pair<int, float> min(-1, FLT_MAX);
        size_t length = ExtractTable.size();

        while(length > 0)
        {
            for (int i = length / 2 - 1; i >= 0; i--)
                heapify(ExtractTable, i, length);
            min = WeightTable[ExtractTable[0]->first];
            Vertex u = RoutingTiles.gVertex(min.first);
            //update the weight of adjacent vertices
            for (size_t i = 0; i < u.gNumL(); i++)
            {
                Edge e = u.glink(i);
                int id = e.gPVertex()->gId();
                if (WeightTable[id].second > WeightTable[min.first].second + e.gWeight())
                {
                    WeightTable[id].second = WeightTable[min.first].second + e.gWeight();
                    TraceTable[id] = min.first;
                }
            }
            swap(ExtractTable[0], ExtractTable[length - 1]);
            length--;
        }

        //Trace back for the end vertex
        //and updating the weight
        int tractor = index_e;
        vector<pair<int, int>> routing;
        while(tractor != index_s)
        {
           RoutingTiles.add_demand( tractor, TraceTable[tractor]);
           routing.insert(routing.begin(), index2pair(tractor, parser.gNumHTiles())); 
           tractor = TraceTable[tractor];
        }
        routing.insert(routing.begin(), source); 

        resultTable.push_back(routing);
    }
    cout << "Done" << endl;

    cout << "Output file...";
    //outputfile
    ofstream outfile;
    outfile.open(argv[2], ios::out);
    
    for(size_t i = 0; i < resultTable.size(); i++)
    {
        outfile << nets[i].first << " " << resultTable[i].size() - 1 << endl;
        for(size_t j = 0; j < resultTable[i].size() - 1; j++)
        {
            outfile << resultTable[i][j].first << " " <<  resultTable[i][j].second << " ";
            outfile << resultTable[i][j + 1].first << " " <<  resultTable[i][j + 1].second << endl;
        }
    }
    outfile.close();
    cout << "Done" << endl;


    cout << "Times: " << timer.End() << endl;
    return 0;
}

int pair2index(pair<int, int> p, int NumH)
{
    return p.first * NumH + p.second;  
}

pair<int, int> index2pair(int i, int NumH)
{
    pair<int, int> p(i / NumH,  i % NumH);
    return p;
}

void swap(pair<int, float>* &a, pair<int, float>* &b)
{ 
    pair<int, float> *temp = a;
    a = b;
    b = temp;
} 

void heapify(vector< pair<int, float>* > &datas, size_t root, size_t length)
{
    size_t leftNode = root * 2 + 1;
    size_t rightNode = root * 2 + 2;
    //default setting the minNode is root
    size_t minNode = root;
    if (leftNode < length && datas[leftNode]->second < datas[minNode]->second)
        minNode = leftNode;
    if (rightNode < length && datas[rightNode]->second < datas[minNode]->second)
        minNode = rightNode;
    if (minNode != root)
    {
        swap(datas[minNode], datas[root]);
        heapify(datas, minNode, length);
    }
}


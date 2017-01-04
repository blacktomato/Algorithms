/*************************************************************
 * File Name : router.cpp
 * Purpose : For global routing problem
 * Creation Date : Thu 22 Dec 2016 09:23:51 PM CST
 * Last Modified : Wed 04 Jan 2017 01:28:21 AM CST
 * Created By : SL Chung
**************************************************************/

#include <iostream>
#include <vector>
#include <fstream>
#include <float.h>
#include "parser.h"
#include "graph.h"

using namespace std;

int pair2index(pair<int, int>, int);
pair<int, int> index2pair(int, int);

int main(int argc, char **argv)
{
    if( argc != 3 ){ cerr << "Usage: ./router [input_file_name] [output_file_name]" << endl; return 1; }

    AlgParser parser;

    // read the file in the first argument
    if( ! parser.read( argv[1] ) ) { cerr << "Fail to open file: " << argv[1] << endl; return 1; }
    
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
    vector<float> WeightTable(NumTile, 0.0);
    vector<int> TraceTable(NumTile, -1);
    
    //For test
    //RoutingTiles.printGraph();
    
    //gNumNet * each length
    vector<vector< pair<int, int> >> resultTable;

    cout << "Dijkstra Algorithm..." << endl;
    //Do the Dijkstra Algorithm for NumNets times 
    for (int idNet = 0; idNet < parser.gNumNets(); ++idNet)
    {
        cout << "Working the " << idNet << " th net..." << endl;
        vector<pair<int, float>> ExtractTable(NumTile, make_pair(0, 0.0));
        pair<int, int> source = parser.gNetStart( idNet );
        pair<int, int> end = parser.gNetEnd( idNet );
        int index_s = pair2index(source, parser.gNumHTiles());
        int index_e = pair2index(end, parser.gNumHTiles());
            
        //initialize the tables for each Dijkstra Algorithm
        for(int i = 0; i < NumTile; i++)
        {
            ExtractTable[i].first = i;
            ExtractTable[i].second = FLT_MAX;
            WeightTable[i] = FLT_MAX;
            TraceTable[i] = -1;
        }

        //Initialize Single Source
        ExtractTable[index_s].second = 0.0;
        WeightTable[index_s] = 0.0;
        TraceTable[index_s] = index_s;

        //Extract min
        pair<int, float> min(-1, FLT_MAX);
        int target = -1;
        while(ExtractTable.size() > 0)
        {
            min = make_pair(-1, FLT_MAX);
            target = -1; //For extraction
            //scan ExtractTable to find the minimun
            for(size_t i = 0; i < ExtractTable.size(); i++)
            {
                //Update ExtractTable
                ExtractTable[i].second = WeightTable[ExtractTable[i].first];
                if(min.second > ExtractTable[i].second)
                {
                    min = ExtractTable[i];
                    target = i;
                }
            }
            //assure the target must be in the Graph
            ExtractTable.erase(ExtractTable.begin() + target);
            Vertex u = RoutingTiles.gVertex(min.first);
            //update the weight of adjacent vertices
            for (size_t i = 0; i < u.gNumL(); i++)
            {
                Edge e = u.glink(i);
                int id = e.gPVertex()->gId();
                if (WeightTable[id] > WeightTable[min.first] + e.gWeight())
                {
                    WeightTable[id] = WeightTable[min.first] + e.gWeight();
                    TraceTable[id] = min.first;
                }
            }
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
        outfile << i << " " << resultTable[i].size() - 1 << endl;
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

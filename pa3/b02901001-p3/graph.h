/*************************************************************
 * File Name : graph.h
 * Purpose : for mapping global routing to graph
 * Creation Date : Sat 24 Dec 2016 10:32:03 PM CST
 * Last Modified : Wed 04 Jan 2017 11:12:07 AM CST
 * Created By : SL Chung
**************************************************************/
#ifndef GRAPH
#define GRAPH

#include <math.h>
#include <iostream>

class Vertex; //For class Edge to regconize class Vertex
class Edge
{
    public:
        Edge(int c = 1, Vertex *g = NULL, int d = 0)
        {
            capacity = c;
            demand = d;
            weight = new_weight();
            go_to = g;
        }
        void point(Vertex *v){ go_to = v; }
        void add_demand()
        {
            demand++;
            weight = new_weight();
        }

        Vertex* gPVertex(){ return go_to; }
        float gWeight(){ return weight; }
    private:
        int capacity;
        int demand;
        float weight;
        Vertex* go_to;
        //loss function
        float new_weight()
        {
            return pow(2.0, (demand/capacity) + 1) - 1;
        }
};

class Vertex
{
    public:
        Vertex(int i){ id = i; }
        int gId(){return id;}
        void linking( Vertex &v, int c )
        {
            Edge e(c, &v, 0);
            link.push_back(e);
        }
        size_t gNumL(){return link.size();}
        Edge& glink(size_t index)
        {
            return link[index];
        }
    private:
        int id;
        vector<Edge> link;
};

class Graph
{
    public:
        Graph(){}
        void add_vertex(int id)
        {
            Vertex v(id);
            vertices.push_back(v);
        }

        void add_link(int from, int to, int c)
        {
            vertices[from].linking(vertices[to], c);
        }

        Vertex gVertex(int index){return vertices[index];}
        void add_demand(int v1, int v2)
        {
            for( size_t i = 0; i < vertices[v1].gNumL(); i++ )
            {
                if (vertices[v1].glink(i).gPVertex()->gId() == v2)
                {
                    vertices[v1].glink(i).add_demand();
                    break;
                }
            }

            for( size_t i = 0; i < vertices[v2].gNumL(); i++ )
            {
                if (vertices[v2].glink(i).gPVertex()->gId() == v1)
                {
                    vertices[v2].glink(i).add_demand();
                    break;
                }
            }
        }
        //For debugging
        void printGraph()
        {
            for(size_t index = 0; index < vertices.size(); index++)
            {
                cout << vertices[index].gId() << endl;
                for(size_t id_link = 0; id_link < vertices[index].gNumL(); id_link++)
                {
                    cout << vertices[index].glink(id_link).gPVertex()->gId() << " ";
                }
                cout << endl;
            }
        }
    private:
        vector<Vertex> vertices;
};

#endif

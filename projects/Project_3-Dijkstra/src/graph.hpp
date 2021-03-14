//
//  graph.hpp
//  Dijkstra
//
//  Created by Allister Liu on 11/11/20.
//

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <list>
#include <sstream>
#include <iterator>

#include "heap.hpp"
#include "hash.hpp"

using namespace std;

class graph{
    public:
        class edge;
        class vertex;
        
        graph();
        bool isVertex(const string &);
        void dijkstra(const string &);
        void makeGraph(ifstream &);
        void insert(const string &, const string &, int);
        void printGraph(ofstream &);
        
        int capacity;
        
        class edge{
            public:
                int cost;
                vertex *destination;
        };
        class vertex{
            public:
                string id;
                bool known;
                int distance;

                list<edge> adjacent;
                list<string> path;
        };

    private:
        list<vertex*> vertexList;
        hashTable *vertices;
};
#endif /* GRAPH_HPP */

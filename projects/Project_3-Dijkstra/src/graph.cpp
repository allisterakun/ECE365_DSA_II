//
//  graph.cpp
//  Dijkstra
//
//  Created by Allister Liu on 11/11/20.
//

#include "graph.hpp"

using namespace std;

graph::graph(){
    vertices = new hashTable(1000000);
    capacity = 0;
}

void graph::makeGraph(ifstream &input){
    int distance;
    string v1, v2;
    while (input >> v1 >> v2 >> distance){
        insert(v1, v2, distance);
    }
}

void graph::printGraph(ofstream &out){
    for(list<vertex *>::const_iterator it = vertexList.begin(); it!= vertexList.end(); ++it){
        out << (*it)->id << ":";
        if ((*it)->distance == INT_MAX){
            out << "NO PATH" << endl;
        }
        else {
            out << (*it) ->distance << "  [";
            for (list<string>::const_iterator i = (*it) ->path.begin(); i!= (*it) ->path.end(); ++i){
                out << *i;
                if (next(i,1)!= (*it) ->path.end()){
                    out << ",";
                }
            }
            out << "]" << endl;
        }
    }
}

void graph::insert( const string &v1, const string &v2, int distance){
    edge newEdge;
    vertex *temp1;
    vertex *temp2;
    
    if (!vertices -> contains(v1)){
        temp1 = new vertex;
        temp1 -> id = v1;
        temp1 -> known = false;
        temp1 -> distance = INT_MAX;
        vertexList.push_back(temp1);
        vertices -> insert(v1, temp1);
        capacity ++;
    }
    else {
        temp1 = (vertex*)vertices -> getPointer(v1);
    }
    if (!vertices -> contains(v2)){
             temp2 = new vertex;
              temp2 -> id = v2;
              temp2 -> known = false;
              temp2 -> distance = INT_MAX;
                vertexList.push_back(temp2);
                vertices -> insert(v2, temp2);
                capacity ++;
    }
    else {
        temp2 = (vertex *)vertices -> getPointer(v2);
    }
    newEdge.destination = temp2;
    newEdge.cost = distance;

    temp1 -> adjacent.push_back(newEdge);
}

void graph::dijkstra(const string &startV){
    vertex *start = (vertex *)vertices -> getPointer(startV);
    start -> distance = 0;
    start -> path.push_back(startV);
    heap disHeap(capacity);


    disHeap.insert(startV, start->distance, start);
    for (list<vertex*>::const_iterator it = vertexList.begin(), end = vertexList.end();
         it != end; ++it){
        if ((*it)-> id != startV){
            disHeap.insert((*it)->id, (*it)->distance, *it);
        }
    }
    vertex *tempV = nullptr;
    for (int i = 0; i < capacity; ++i){
        disHeap.deleteMin(nullptr, nullptr, &tempV);
        tempV-> known = true;
        for (list<edge>::const_iterator it = tempV->adjacent.begin(), end = tempV->adjacent.end(); it != end && tempV->distance != INT_MAX; ++it){
            if ( (!it -> destination->known)    &&  (it->destination->distance > (it ->cost + tempV -> distance))   &&  (tempV -> distance != INT_MAX) ){
                
                it->destination->path.assign(tempV->path.begin(), tempV->path.end());
                it->destination->path.push_back(it->destination->id);

                it->destination->distance = it->cost + tempV ->distance;
                disHeap.setKey(it->destination->id, it->destination->distance);
            }
        }
            }
}

bool graph::isVertex(const string &v){
    return (vertices -> contains(v));
}

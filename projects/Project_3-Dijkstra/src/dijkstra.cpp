//
//  dijkstra.cpp
//  Dijkstra
//
//  Created by Allister Liu on 11/11/20.
//

#include "heap.hpp"
#include "hash.hpp"
#include "graph.hpp"

#include <chrono>

using namespace std;
int main(int argc, const char * argv[]) {
    string inFile, outFile;
    ifstream input;
    ofstream output;
    graph myDijkstra;
    string startV;

    
    while (!input.is_open()){
        cout << "Please enter graph input file path:" << endl << ">: ";
        cin >> inFile;
        input.open(inFile, ifstream::in);
        if(!input.is_open()){
            fprintf(stderr, "ERROR opening input file: %s\n", strerror(errno));
            cout << "INVALID INPUT, please try again." << endl;
        }
    }
    
    myDijkstra.makeGraph(input);
    input.close();

    while(!myDijkstra.isVertex(startV)){
        cout << "Plaese enter a start vertex :"  << endl << ">: ";
        cin >> startV;
        if(!myDijkstra.isVertex(startV))
            cout << "INVALID INPUT, please try again." << endl;

    }
    clock_t start = clock();
    myDijkstra.dijkstra(startV);
    clock_t end = clock();
    cout << "Total Time (in seconds) to apply Dijkstra algorithm :" << (float(end - start))/CLOCKS_PER_SEC << endl;

    while(!output.is_open()){
        cout << "Please enter graph output file path:" << endl << ">: ";
        cin >> outFile;
        output.open(outFile, ofstream::out | ofstream::trunc);
        if(!output.is_open()){
            fprintf(stderr, "ERROR creating input file: %s\n", strerror(errno));
            cout << "INVALID INPUT, please try again." << endl;
        }
    }
    
    myDijkstra.printGraph(output);
    output.close();
    return 0;
}

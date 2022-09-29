#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;


bool graphBuilderAdjacencyMatrix(ifstream& infile, int numberVertex, int edge , int Vertex_a, int Vertex_b) {
        
    bool graph[numberVertex][numberVertex] = {false};
            
    while(infile >> Vertex_a >> Vertex_b) {
        graph[Vertex_a][Vertex_b] = true;
        graph[Vertex_b][Vertex_a] = true;
        edge++;
    }

    return graph;
}



bool graphBuilderAdjacencyVector(ifstream& infile, int numberVertex, vector<bool>  graphLL[], int Vertex_a, int Vertex_b) {
            
    while(infile >> Vertex_a >> Vertex_b) {
        graphLL[Vertex_a].push_back(Vertex_b);
        graphLL[Vertex_b].push_back(Vertex_a);
    }

    return graphLL;
    
}
 

int main() {

    ifstream infile("data.txt");

	int numberVertex,Vertex_a, Vertex_b, edge=0;
    infile >> numberVertex;
    vector<bool> graphLL[numberVertex]; 
 

    clock_t start, end;
    double cpu_time_used;



	start = clock();
    
    graphBuilderAdjacencyMatrix(infile, numberVertex, edge, Vertex_a, Vertex_b);
	graphBuilderAdjacencyVector(infile, numberVertex, graphLL,  Vertex_a, Vertex_b);

    end = clock();

    cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
    cout << cpu_time_used;

	infile.close();

	return 0;
}

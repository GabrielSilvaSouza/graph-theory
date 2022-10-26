#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <utility>
#include <bits/stdc++.h>
#include <tuple>

using namespace std;
using namespace std::chrono;



class Graph { //class created

    int root; //root will be needed for the heap function

    vector< tuple <int, float> > * v_w;  // a vector of tuple to store number and weight

public:

    void graphBuilderAdjacencyVector(int numberVertex, vector< tuple <int, float> > graphLL[],  int Vertex_a, int Vertex_b); //builder metohd

};


void Graph::graphBuilderAdjacencyVector(int numberVertex, vector< tuple <int, float> >  graphLL[], int Vertex_a, int Vertex_b) {
            
    int weight;
    ifstream infile("grafo_1.txt");
    while(infile >> weight >> Vertex_a >> Vertex_b ) {

        graphLL[Vertex_a].push_back(make_tuple(Vertex_b,weight)); //insert a linked list inside a vector
        sort(graphLL[Vertex_a].begin(), graphLL[Vertex_a].end()); //sort the vector 
        graphLL[Vertex_b].push_back(make_tuple(Vertex_a,weight));
        sort(graphLL[Vertex_b].begin(), graphLL[Vertex_b].end());

    // #is it posssible to optimize the sorting function? (it walks on the vector in each loop) --> can it be better?

    }
    infile.close();

/*  //print function to check on vertex
    for (const auto& i : graphLL[67] ) {
        cout << get<0>(i) << endl;
    }
*/
}
 

int main() {
    
    ifstream infile("grafo_1.txt"); //initialize graph

	int numberVertex, Vertex_a, Vertex_b, edge=0;

    infile >> numberVertex;
    vector< tuple <int, float> > graphLL[numberVertex+1];

    infile.close(); // end of initialization (obs: the allocation will explode with higher graphs, must use alloc (sizeof())
    
    clock_t start, end;
    double cpu_time_used;

    Graph u; //create an object

	start = clock();
    
	u.graphBuilderAdjacencyVector(numberVertex, graphLL,  Vertex_a, Vertex_b); //builder

    end = clock();
  
    cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
    cout << cpu_time_used;
   
	return 0;
    
}

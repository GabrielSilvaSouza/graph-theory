#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

class Node
{
    public:
    int data;
    Node *next;
};

bool graphBuilderMatrix(ifstream& infile, int numberVertex, int edge , int Vertex_a, int Vertex_b) {
	
	bool graph[numberVertex][numberVertex] = {false}; //the memory will explode. must use pointers here
	
	while(infile >> Vertex_a >> Vertex_b) {
        graph[Vertex_a][Vertex_b] = true;
        graph[Vertex_b][Vertex_a] = true;
		edge++;
	}

	return graph;
}


void graphBuilderLL(int model){
	int i,j;
	int n = 0;

	for(i=0; i < n; i++){
		for(j = 0; j < n; j++) {

			if (i<j) {

			}	

		}

	}
	

}

int main() {

	int numberVertex;
	int edge=0;
	int Vertex_a, Vertex_b;
	bool model;
	ifstream infile("data.txt");
	infile >> numberVertex;
	auto start = high_resolution_clock::now();
	model = graphBuilderMatrix(infile, numberVertex, edge, Vertex_a, Vertex_b);
	graphBuilderLL(model);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
    	cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
	infile.close();
	return 0;
}
#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

class Node {
    public:
        int data;
        Node* next;
};

void graphBuilderMatrix(ifstream& infile) {

	int numberVertex;
	int edge=0;
	int Vertex_a, Vertex_b;
	
	infile >> numberVertex;
	////----> int *graph = (int*) malloc (sizeof (int) * (n*n)); */
	bool graph[numberVertex][numberVertex] = {false};
	
	while(infile >> Vertex_a >> Vertex_b) {
        graph[Vertex_a][Vertex_b] = true;
        graph[Vertex_b][Vertex_a] = true;
		edge++;
	}
	cout << edge;
    cout << "\n";
}

void graphBuilderList(ifstream& infile) {

	int numberVertex;
	int edge=0;
	int Vertex_a, Vertex_b;
	
	infile >> numberVertex;
	////----> int *graph = (int*) malloc (sizeof (int) * (n*n)); */
	bool graph[numberVertex] = {false};
	
	/*while(infile >> Vertex_a >> Vertex_b) {
        graph[Vertex_a][Vertex_b] = true;
        graph[Vertex_b][Vertex_a] = true;
		edge++;
	}*/
	cout << edge;
    cout << "\n";
}



int main() {
	ifstream infile("data.txt");
	auto start = high_resolution_clock::now();
	graphBuilderMatrix(infile);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
    	cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
	infile.close();
	return 0;
}
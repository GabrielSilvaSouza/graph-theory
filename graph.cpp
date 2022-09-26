#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
using namespace std;
using namespace std::chrono;

class Graph {
    public:
        void input() {

        }

        void output() {

            cout << Graph.findConnectedComponent()

            return textFile
        }

        void breadthFirstSearch() {

        }

        void depthFirstSearch() {

        }

        void findDistance() {

        }

        void findDiameter() {

        }

        void findConnectedComponent() {

        }
}

class AdjacencyMatrix: public Graph {
    public:
        bool graphBuilderAdjacencyMatrix(ifstream& infile, int numberVertex, int edge , int Vertex_a, int Vertex_b) {
        
        bool graph[numberVertex][numberVertex] = {false};
        
        while(infile >> Vertex_a >> Vertex_b) {
            graph[Vertex_a][Vertex_b] = true;
            graph[Vertex_b][Vertex_a] = true;
            edge++;
        }

        return graph;
    }
}

class AdjacencyVector: public Graph {
    public:
        void graphBuilderAdjacencyVector(vector<bool> graph, int n, std::vector<vector<bool>> model) {
        
        for(int i=0; i < n; i++){
            for(int j = 0; j < n; j++) {
                if (i<j && model[i][j] == true) {
                    //colocar "for" e carregar os objetos
                    graph[i] = {};
                }
            }
        }
    }
} 

int main() {

	int numberVertex,Vertex_a, Vertex_b, edge=0;
	vector<bool> model;
	ifstream infile("data.txt");
	infile >> numberVertex;
	model[numberVertex];

	auto start = high_resolution_clock::now();

	std::vector<vector<bool>> u { graphBuilderMatrix(infile, numberVertex, edge, Vertex_a, Vertex_b)};
	//graphBuilderLL(model, numberVertex, u);

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
    	cout << "Time taken by function: "
        << duration.count() << " microseconds" << endl;

	infile.close();
	return 0;
}

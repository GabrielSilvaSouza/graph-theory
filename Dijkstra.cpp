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

    vector< tuple <int, float> > * graphLL;  // a vector of tuple to store number and weight

    int numberVertex;

public:

    Graph(int n) 
    {

        ifstream infile("grafo_1.txt"); 
        int numberVertex;
        infile >> numberVertex;
        infile.close();

        this->numberVertex = numberVertex;

        graphLL = new vector< tuple <int, float> > [numberVertex+1];
    }

    void graphBuilderAdjacencyVector(int Vertex_a, int Vertex_b) 
    {
            
        int weight;
        int jump;
        ifstream infile("grafo_1.txt");
        infile >> weight;

        while(infile >> Vertex_a >> Vertex_b >> weight ) {
            graphLL[Vertex_a].push_back(make_tuple(Vertex_b,weight)); //insert a linked list inside a vector
            sort(graphLL[Vertex_a].begin(), graphLL[Vertex_a].end()); //sort the vector 
            graphLL[Vertex_b].push_back(make_tuple(Vertex_a,weight));
            sort(graphLL[Vertex_b].begin(), graphLL[Vertex_b].end());

        }
        infile.close();
    
    

    } 
    

    void dijkstra(int start, int end, int numberVertex) 
    {

        vector<float> dist(numberVertex, numeric_limits<float>::infinity());
        list<int> explored;
        explored.push_back(start);
        list<int> found; 
        found.push_back(start);
        dist[start] = 0;


        while (explored.size() != dist.size())
        {

            for (const auto& v : graphLL[start]) 
            {

                if (std::find(explored.begin(), explored.end(), get<0>(v) ) == explored.end()) {
                    found.push_back(get<0>(v));
                }
                
                if (dist[get<0>(v)] > (dist[start] + get<1>(v))) {
                    dist[get<0>(v)] = dist[start] + get<1>(v);
                }

            }

            start = found.front();
            explored.push_back(found.front());
            found.pop_front();

        }
        
        for (const auto& i : dist ) {
            cout << i << endl;
        }

    }
  
};

int main() {
    

    int Vertex_a, Vertex_b;
    clock_t start, end;
    double cpu_time_used;

    Graph u(0); //create an object

	start = clock();
	u.graphBuilderAdjacencyVector(Vertex_a, Vertex_b); //builder
    u.dijkstra(2,1,6);
    end = clock();
  
    cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
    
    cout << "\n";

    cout << "Tempo gasto: " << cpu_time_used;
   
	
    
    return 0;
    
}

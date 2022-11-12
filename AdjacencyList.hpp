#include <fstream>
#include <iostream>
#include <string>
#include "LinkedList.hpp"

class AdjacencyList {

    public:
        int number_vertex;
        LinkedList* linked_list_array;

        AdjacencyList(std::string);
};

AdjacencyList::AdjacencyList(std::string file_name) { // O(V+E)

    int vertex, adjancent_vertex;
    float edge_weight;
    std::ifstream infile(file_name);
    
    infile >> number_vertex;
    linked_list_array = new LinkedList[number_vertex](); // O(V)

    while(infile >> vertex >> adjancent_vertex >> edge_weight) { // O(E)
        linked_list_array[vertex-1].insert(adjancent_vertex, edge_weight);
        linked_list_array[adjancent_vertex-1].insert(vertex, edge_weight);
    }
    
    infile.close();
}
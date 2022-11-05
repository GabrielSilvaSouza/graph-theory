#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Node_Linked_List {

    public:
        int data;
        Node_Linked_List* next_node;
        float edge_weight;

        Node_Linked_List() {
            data = 0;
            next_node = NULL;
        }

        Node_Linked_List(int data) {
            this->data = data;
            this->next_node = NULL;
        }

        Node_Linked_List(int, float);
};

Node_Linked_List::Node_Linked_List(int data, float new_edge_weight) {
    
    this->data = data;
    this->next_node = NULL;
    edge_weight = new_edge_weight;
}

class Linked_List {
    
    public:
        Node_Linked_List* head_linked_list;
        int size_linked_list;

        Linked_List() {
            head_linked_list = NULL;
        }
    
        void insert(int);
        void insert(int, float);
        void print_linked_list();
};

void Linked_List::insert(int data) {

    Node_Linked_List* new_node = new Node_Linked_List(data);
    new_node->next_node = head_linked_list;
    this->head_linked_list = new_node;
    size_linked_list += 1;
}

void Linked_List::insert(int data, float edge_weight) {

    Node_Linked_List* new_node = new Node_Linked_List(data, edge_weight);
    new_node->next_node = head_linked_list;
    this->head_linked_list = new_node;
    size_linked_list += 1;
}

void Linked_List::print_linked_list() {

    Node_Linked_List* temporary = head_linked_list;

    if (head_linked_list == NULL) {
        cout << "List empty" << endl;
        return;
    }

    while (temporary != NULL) {
        cout << temporary->data << " ";
        temporary = temporary->next_node;
    }
}

class Prioriy_Queue {

};

class Binary_Heap {

};

class Graph {

    public:
        int number_vertex;
        vector<Linked_List> graph_representation;

        void graph_builder_adjacency_list(string);
        float get_distance();
        void shortest_path();
        void dijkstra_algorithm(int);
        void minimum_spanning_tree();
};

void Graph::graph_builder_adjacency_list(string file_name) {

    int number_vertex, vertex_v, neighboring_vertex_v;
    float edge_weight;
    ifstream infile(file_name);
    infile >> number_vertex;
    graph_representation.resize(number_vertex);

    while(infile >> vertex_v >> neighboring_vertex_v >> edge_weight) {
        graph_representation[vertex_v-1].insert(neighboring_vertex_v, edge_weight);
        graph_representation[neighboring_vertex_v-1].insert(vertex_v, edge_weight);
    }
    
    infile.close();
}

float Graph::get_distance() {

}

void Graph::shortest_path() {

}

void Graph::dijkstra_algorithm(int start_vertex) {
    
    vector<float> distance_vector(number_vertex, numeric_limits<float>::infinity());
    Linked_List explored_set;
    distance_vector[start_vertex-1] = 0;
    explored_set.insert(start_vertex);

    for (int i = 0; i < number_vertex; i++) {
    }
    
    for (int i = 0; i < graph_representation[start_vertex].size_linked_list; i++) {
        Node_Linked_List* temporary = graph_representation[start_vertex].head_linked_list;
        distance_vector[temporary->data] = temporary->edge_weight;
        temporary = temporary->next_node;
    }

    while(explored_set.size_linked_list != number_vertex) {
        
    }

    for (const auto& i : distance_vector) {
        cout << i << endl;
    }

    //return distance_vector
}

void Graph::minimum_spanning_tree() {

}

int main() {

    Graph graph_test;

    graph_test.graph_builder_adjacency_list("grafo_W_5_1.txt");
    
    return 0;
}

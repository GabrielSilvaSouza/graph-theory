#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node_Linked_List {

    public:
        int data_int;
        float data_float;
        Node_Linked_List* next_node;

        Node_Linked_List(int, float);
};

Node_Linked_List::Node_Linked_List(int new_data_int = -1, float new_data_float = -1.0) { // O(1)
    
    this->data_int = new_data_int;
    this->data_float = new_data_float;
    this->next_node = NULL;
}

class Linked_List {
    
    public:
        Node_Linked_List* head_linked_list;
        int size_linked_list;

        Linked_List();
        void insert(int, float);
        void print_linked_list();
};

Linked_List::Linked_List() {
    head_linked_list = NULL;
    size_linked_list = 0;
}

void Linked_List::insert(int new_data_int = 0, float new_data_float = 0.0) { // O(1)

    Node_Linked_List* new_node = new Node_Linked_List(new_data_int, new_data_float);
    new_node->next_node = head_linked_list;
    this->head_linked_list = new_node;
    size_linked_list += 1;
}

class Node_Binary_Heap {

    public:
        float data_float;
        int data_int;
        Node_Binary_Heap(int, float);
};

Node_Binary_Heap::Node_Binary_Heap(int new_data_int = -1, float new_data_float = -1.0) {

    this->data_int = new_data_int;
    this->data_float = new_data_float;
}

class Binary_Heap {
    
    public:
        vector<Node_Binary_Heap> heap_array;
        vector<Node_Binary_Heap*> auxiliar_pointers;
        int currrent_heap_size;
        int maximum_heap_size;

        int parent(int i) {return (i-1)/2;}
        int left_child(int i) {return (2*i + 1);}
        int right_child(int i) {return (2*i + 2);}

        Binary_Heap(int);
        void swap_heap_array(Node_Binary_Heap*, Node_Binary_Heap*);
        void swap_auxiliar_pointers(Node_Binary_Heap*&, Node_Binary_Heap*&);
        void heapify(int);
        void insert(float, int);
        int pop();
};

Binary_Heap::Binary_Heap(int new_maximum) { // O(1)

    currrent_heap_size = 0;
    maximum_heap_size = new_maximum;
    heap_array.resize(new_maximum);
    auxiliar_pointers.resize(new_maximum);
}

void Binary_Heap::swap_heap_array(Node_Binary_Heap *x, Node_Binary_Heap *y) { // O(1)

    Node_Binary_Heap temp = *x;
    *x = *y;
    *y = temp;
}

void Binary_Heap::swap_auxiliar_pointers(Node_Binary_Heap *&x, Node_Binary_Heap *&y) { // O(1)

    Node_Binary_Heap* temp = x;
    x = y;
    y = temp;
}

void Binary_Heap::insert(float key, int value) { // O(log V)

    if (currrent_heap_size == maximum_heap_size) {
        cout << "\nOverflow: Could not insert key\n";
        return;
    }

    int index = currrent_heap_size;
    currrent_heap_size++;
    heap_array[index].data_float = key;
    heap_array[index].data_int = value;
    auxiliar_pointers[value] = &heap_array[index];

    while ((index != 0) && (heap_array[parent(index)].data_float > heap_array[index].data_float)) {
        swap_heap_array(&heap_array[index], &heap_array[parent(index)]);
        swap_auxiliar_pointers(auxiliar_pointers[index], auxiliar_pointers[parent(index)]);
        index = parent(index);
    }
}

void Binary_Heap::heapify(int index = 0) { // O(V)

    bool done = false;
    int new_root = 0;

    while(!done) {

        new_root = index;

        if ((left_child(index) < currrent_heap_size) && (heap_array[left_child(index)].data_float < heap_array[index].data_float)) {
            new_root = left_child(index);
        }
        if ((right_child(index) < currrent_heap_size) && (heap_array[right_child(index)].data_float < heap_array[new_root].data_float)) {
            new_root = right_child(index);
        }
        if (new_root != index) {
            swap_heap_array(&heap_array[new_root], &heap_array[index]);
            swap_auxiliar_pointers(auxiliar_pointers[new_root], auxiliar_pointers[index]);
            index = new_root;
        } else {done = true;}
    }
}

int Binary_Heap::pop() { // O(1)

    if (currrent_heap_size <= 0) {return -1;}
    if (currrent_heap_size == 1) {
        currrent_heap_size--;
        return heap_array[0].data_int;
    }
    
    int root = heap_array[0].data_int;
    heap_array[0] = heap_array[currrent_heap_size-1];
    currrent_heap_size--;
    auxiliar_pointers[root] = NULL;
    heapify();

    return root;
}

class Graph {

    public:
        int number_vertex;
        vector<Linked_List> graph_representation;
        vector<int> parent;

        Graph();
        void graph_builder_adjacency_list(string, bool);
        void dijkstra_algorithm(int);
};

Graph::Graph() {
    number_vertex = 0;
}

void Graph::graph_builder_adjacency_list(string file_name, bool graph_weight = false) { // O(n+m)

    int vertex_v, neighboring_vertex_v;
    float edge_weight;
    ifstream infile(file_name);
    infile >> number_vertex;
    graph_representation.resize(number_vertex); // O(n)

    if (graph_weight == true) {
        while(infile >> vertex_v >> neighboring_vertex_v >> edge_weight) { // O(m)
            graph_representation[vertex_v-1].insert(neighboring_vertex_v, edge_weight);
            graph_representation[neighboring_vertex_v-1].insert(vertex_v, edge_weight);
        }
    } else if (graph_weight == false) {
        while(infile >> vertex_v >> neighboring_vertex_v) { // O(m)
            graph_representation[vertex_v-1].insert(neighboring_vertex_v);
            graph_representation[neighboring_vertex_v-1].insert(vertex_v);
        }
    }
    
    infile.close();
}

void Graph::dijkstra_algorithm(int start_vertex) { // O((V+E)*log V)
    
    vector<float> distance_vector(number_vertex, numeric_limits<float>::infinity());
    Linked_List explored_set;
    distance_vector[start_vertex-1] = 0.0;
    Binary_Heap not_explored_set(number_vertex);
    Node_Linked_List* neighboring_vertex;
    not_explored_set.insert(0.0, start_vertex);
    float zero = 0.0;
    int exploring_vertex;
    
    while(explored_set.size_linked_list != number_vertex) {
        
        exploring_vertex = not_explored_set.pop();
        explored_set.insert(exploring_vertex);
        neighboring_vertex = graph_representation[exploring_vertex-1].head_linked_list;

        for (int i = 0; i < graph_representation[exploring_vertex-1].size_linked_list; i++) {

            if (neighboring_vertex->data_float < zero) {
                cout << "The library still doesn't implement shortest paths with negative weights.";
            }
            
            else if (distance_vector[neighboring_vertex->data_int-1] > distance_vector[exploring_vertex-1] + neighboring_vertex->data_float) {
                
                distance_vector[neighboring_vertex->data_int-1] = distance_vector[exploring_vertex-1] + neighboring_vertex->data_float;
                if (not_explored_set.auxiliar_pointers[neighboring_vertex->data_int-1] != NULL) {
                    not_explored_set.auxiliar_pointers[neighboring_vertex->data_int-1]->data_float = distance_vector[exploring_vertex-1] + neighboring_vertex->data_float;
                    not_explored_set.heapify(&*not_explored_set.auxiliar_pointers[neighboring_vertex->data_int-1] - &not_explored_set.heap_array[0]);
                } else if (not_explored_set.auxiliar_pointers[neighboring_vertex->data_int-1] == NULL) {
                    not_explored_set.insert(distance_vector[neighboring_vertex->data_int-1], neighboring_vertex->data_int);
                }
            }
            neighboring_vertex = neighboring_vertex->next_node;
        }
    }

    int count = 0;
    for(const auto& i: distance_vector) {
        cout << count+1 << " " << i << endl;
        count++;
    }
}

int main() {

    Graph test;
    test.graph_builder_adjacency_list("grafo_W_1_1.txt", true);

    clock_t start, end;
    double cpu_time_used;
    start = clock();
    test.dijkstra_algorithm(1);
    end = clock();
    cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
    cout << "Tempo gasto: " << cpu_time_used << '\n';

    return 0;
}

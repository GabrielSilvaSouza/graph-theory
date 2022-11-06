#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Node_Linked_List {

    public:
        int data_int;
        Node_Linked_List* next_node;
        float data_float;

        Node_Linked_List() {
            data_int = 0;
            next_node = NULL;
        }

        Node_Linked_List(int data_int) {
            this->data_int = data_int;
            this->next_node = NULL;
        }

        Node_Linked_List(int, float);
};

Node_Linked_List::Node_Linked_List(int new_data_int, float new_data_float) {
    
    this->data_int = new_data_int;
    this->next_node = NULL;
    data_float = new_data_float;
}

class Linked_List {
    
    public:
        Node_Linked_List* head_linked_list;
        int size_linked_list;

        Linked_List() {head_linked_list = NULL;}
    
        void insert(int);
        void insert(int, float);
        void print_linked_list();
};

void Linked_List::insert(int data_int) {

    Node_Linked_List* new_node = new Node_Linked_List(data_int);
    new_node->next_node = head_linked_list;
    this->head_linked_list = new_node;
    size_linked_list += 1;
}

void Linked_List::insert(int data_int, float data_float) {

    Node_Linked_List* new_node = new Node_Linked_List(data_int, data_float);
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
        cout << temporary->data_int << " ";
        temporary = temporary->next_node;
    }
}

class Prioriy_Queue {

};

class Node_Binary_Heap {

    public:
        float data_float;
        int data_int;
};

class Binary_Heap {
    
    public:
        Node_Binary_Heap *heap_array;
        int currrent_heap_size;
        int maximum_heap_size;

        int parent(int i) {return (i-1)/2;}
        int left_child(int i) {return (2*i + 1);}
        int right_child(int i) {return (2*i + 2);}

        Binary_Heap(int);
        void swap(Node_Binary_Heap*, Node_Binary_Heap*);
        void heapify(int);
        void insert(float, int);
        int pop();
};

Binary_Heap::Binary_Heap(int maximum) {

    currrent_heap_size = 0;
    maximum_heap_size = maximum;
    heap_array = new Node_Binary_Heap[maximum];
}

void Binary_Heap::swap(Node_Binary_Heap *x, Node_Binary_Heap *y) {

    Node_Binary_Heap temp = *x;
    *x = *y;
    *y = temp;
}

void Binary_Heap::insert(float key, int value) {

    if (currrent_heap_size == maximum_heap_size) {
        cout << "\nOverflow: Could not insert key\n";
        return;
    }

    int position = currrent_heap_size;
    currrent_heap_size++;
    heap_array[position].data_float = key;
    heap_array[position].data_int = value;
  
    while ((position != 0) && (heap_array[parent(position)].data_float > heap_array[position].data_float)) {
       swap(&heap_array[position], &heap_array[parent(position)]);
       position = parent(position);
    }
}

void Binary_Heap::heapify(int position) {

    bool done = false;
    int new_root = 0;

    while(!done) {

        new_root = position;

        if ((left_child(position) < currrent_heap_size) && (heap_array[left_child(position)].data_float < heap_array[position].data_float)) {
            new_root = left_child(position);
        } else {
            new_root = position;
        }
        if ((right_child(position) < currrent_heap_size) && (heap_array[right_child(position)].data_float < heap_array[new_root].data_float)) {
            new_root = right_child(position);
        }
        if (new_root != position) {
            heap_array[position], heap_array[new_root] = heap_array[new_root], heap_array[position];
            position = new_root;
        } else {done = true;}
    }
}

int Binary_Heap::pop() {
    if (currrent_heap_size <= 0) {return -1;}
    if (currrent_heap_size == 1) {
        currrent_heap_size--;
        return heap_array[0].data_int;
    }
    
    int root = heap_array[0].data_int;
    heap_array[0] = heap_array[currrent_heap_size-1];
    currrent_heap_size--;
    heapify(0);

    return root;
}

class Graph {

    public:
        int number_vertex;
        vector<Linked_List> graph_representation;
        int *auxiliar_heap_array;

        void graph_builder_adjacency_list(string);
        float get_distance();
        void shortest_path();
        void dijkstra_algorithm(int);
        void minimum_spanning_tree();
};

void Graph::graph_builder_adjacency_list(string file_name) { // O(n+m)

    int number_vertex, vertex_v, neighboring_vertex_v;
    float edge_weight;
    ifstream infile(file_name);
    infile >> number_vertex;
    graph_representation.resize(number_vertex); // O(n)

    while(infile >> vertex_v >> neighboring_vertex_v >> edge_weight) { // O(m)
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
        distance_vector[temporary->data_int] = temporary->data_float;
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
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    graph_test.graph_builder_adjacency_list("grafo_W_5_1.txt"); // 5*10**6
    end = clock();
    cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
    cout << "\n" << "Tempo gasto: " << cpu_time_used;
    return 0;
}

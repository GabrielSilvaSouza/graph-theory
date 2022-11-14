#include "AdjacencyList.hpp"
#include "BinaryHeap.hpp"

class Graph {

    public:
        int number_vertex;
        AdjacencyList* representation;

        Graph();
        void builder_adjacency_list(std::string);
        void uniform_cost_search_array(int, int);
        void uniform_cost_search_heap(int, int);
        void find_mst_heap(int);
};

Graph::Graph() {

    representation = nullptr;
    number_vertex = 0;
}

void Graph::builder_adjacency_list(std::string file_name) { // O(V+E)

    representation = new AdjacencyList(file_name);
    number_vertex = representation->number_vertex;
}


void Graph::uniform_cost_search_array(int start_vertex, int end_vertex) { // O(V**2)
    
    float* distance = new float[number_vertex]{};
    float* discovered = new float[number_vertex]{};
    int* parent = new int[number_vertex]{};
    int next_vertex, index_min;
    NodeLinkedList* adjancent_vertex;

    for (int i = 0; i < number_vertex; i++) {
        distance[i] = 1000000000000.0f;
        discovered[i] = 1000000000000.0f;
    }

    distance[start_vertex-1] = 0.0f;
    discovered[start_vertex-1] = 0.0f;

    for (int explored_set_size = 0; explored_set_size < number_vertex; explored_set_size++) {

        index_min = 0;
        
        for (int i = 0; i < number_vertex; i++) {
            if (discovered[i] < discovered[index_min]) {
                index_min = i;
            }
        }

        discovered[index_min] = 1000000000000.0f;
        next_vertex = index_min;
        adjancent_vertex = representation->linked_list_array[next_vertex].head;
        
        for (int i = 0; i < representation->linked_list_array[next_vertex].size; i++) {
            
            if (adjancent_vertex->data_float < 0.0f) {
                std::cout << "The library still doesn't implement shortest paths with negative weights.";
                return;
            } else if (distance[adjancent_vertex->data_int-1] > distance[next_vertex] + adjancent_vertex->data_float) {
                distance[adjancent_vertex->data_int-1] = distance[next_vertex] + adjancent_vertex->data_float;
                parent[adjancent_vertex->data_int-1] = next_vertex;
                discovered[adjancent_vertex->data_int-1] = distance[next_vertex] + adjancent_vertex->data_float;
            }

            adjancent_vertex = adjancent_vertex->next_node;
        }

        if (next_vertex == end_vertex) {
            break;
        }
    }
}

void Graph::uniform_cost_search_heap(int start_vertex, int end_vertex) { // O((V+E)logV)

    float* distance = new float[number_vertex]{};
    int* parent = new int[number_vertex]{};
    BinaryHeap discovered(number_vertex);
    NodeLinkedList* adjancent_vertex;
    int next_vertex;
    
    for (int i = 0; i < number_vertex; i++) {
        distance[i] = 1000000000000.0f;
    }

    distance[start_vertex-1] = 0.0f;
    discovered.insert(0.0f, start_vertex);
    
    for (int explored_set_size = 0; explored_set_size < number_vertex; explored_set_size++) {
        
        next_vertex = discovered.extract_min();
        adjancent_vertex = representation->linked_list_array[next_vertex-1].head;

        for (int i = 0; i < representation->linked_list_array[next_vertex-1].size; i++) {
            if (adjancent_vertex->data_float < 0.0f) {
                std::cout << "The library still doesn't implement shortest paths with negative weights.";
                return;
            } else if (distance[adjancent_vertex->data_int-1] > (distance[next_vertex-1] + adjancent_vertex->data_float)) {

                distance[adjancent_vertex->data_int-1] = distance[next_vertex-1] + adjancent_vertex->data_float;
                parent[adjancent_vertex->data_int-1] = next_vertex;

                if (discovered.auxiliar_pointers[adjancent_vertex->data_int-1] == nullptr) {
                    discovered.insert(distance[adjancent_vertex->data_int-1], adjancent_vertex->data_int);
                } else {
                    discovered.decrease_key((&*discovered.auxiliar_pointers[adjancent_vertex->data_int-1] - &discovered.heap_array[0]), (distance[next_vertex-1] + adjancent_vertex->data_float));
                }
            }
            
            adjancent_vertex = adjancent_vertex->next_node;
        }

        if (next_vertex == end_vertex) {
            break;
        }
    }
}

void Graph::find_mst_heap(int start_vertex) {
    

    float* distance = new float[number_vertex]{};
    int* parent = new int[number_vertex]{};
    BinaryHeap discovered(number_vertex);
    NodeLinkedList* adjancent_vertex;
    int next_vertex;

    for (int i = 0; i < number_vertex; i++) {
        distance[i] = 1000000000000.0f;
        discovered.insert(1000000000000.0f, i+1);
    }
    
    std::ofstream mst_file ("MST.txt");
    distance[start_vertex-1] = 0.0f;
    discovered.auxiliar_pointers[start_vertex-1]->key = 0.0f;   
    discovered.heapify_up(&*discovered.auxiliar_pointers[start_vertex-1] - &discovered.heap_array[0]);

    mst_file << number_vertex << "\n";

    for (int explored_set_size = 0; explored_set_size < number_vertex; explored_set_size++) {
        
        distance[discovered.heap_array[0].value-1] = discovered.heap_array[0].key;
        next_vertex = discovered.extract_min();
        adjancent_vertex = representation->linked_list_array[next_vertex-1].head;

        for (int i = 0; i < representation->linked_list_array[next_vertex-1].size; i++) {

            if (adjancent_vertex->data_float < 0.0f) {
                std::cout << "The library still doesn't implement shortest paths with negative weights.";
                return;
            } else if ((distance[adjancent_vertex->data_int-1] > adjancent_vertex->data_float) && (discovered.auxiliar_pointers[adjancent_vertex->data_int-1] != nullptr)) {
                distance[adjancent_vertex->data_int-1] = adjancent_vertex->data_float;
                discovered.auxiliar_pointers[adjancent_vertex->data_int-1]->key = adjancent_vertex->data_float;
                discovered.heapify_up(&*discovered.auxiliar_pointers[adjancent_vertex->data_int-1] - &discovered.heap_array[0]);
                parent[adjancent_vertex->data_int-1] = next_vertex;
            }

            adjancent_vertex = adjancent_vertex->next_node;
        }
        
        if (mst_file.is_open()) {
            mst_file << next_vertex << " " << discovered.heap_array[0].value<< " " << discovered.heap_array[0].key << "\n";
        }
    }

    float total_weight = 0.0f;

    for (int i = 0; i < number_vertex; i++) {
        total_weight += distance[i];
    }

    mst_file << total_weight;
    mst_file.close();
}
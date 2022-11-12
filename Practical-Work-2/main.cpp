#include <chrono>
#include "Graph.hpp"

int main() {
    
    Graph graph;
    clock_t start, end;
    double cpu_time_used;
    
    graph.builder_adjacency_list("grafo_W_5_1.txt");
    start = clock();
    graph.uniform_cost_search_heap(10, 20);
    graph.uniform_cost_search_heap(10, 30);
    graph.uniform_cost_search_heap(10, 40);
    graph.uniform_cost_search_heap(10, 50);
    graph.uniform_cost_search_heap(10, 60);
    end = clock();
    cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
    std::cout << "Tempo gasto: " << cpu_time_used/5.0 << '\n';

    return 0;
}
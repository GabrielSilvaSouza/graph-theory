void Graph::dijkstra_vector(int start_vertex, string file_name){

    priority_queue < tuple <float, int>, vector<tuple<float,int>>, greater< tuple<float, int> >  > heapgraph;


    vector<float> distance_vector(number_vertex, numeric_limits<float>::infinity());
    vector<int> explored_set;
    distance_vector[start_vertex-1] = 0.0;
    Node_Linked_List* neighboring_vertex;
    float zero = 0.0;
    int exploring_vertex = start_vertex;
    
    while(explored_set.size() != number_vertex) {
        
        neighboring_vertex = graph_representation[exploring_vertex-1].head_linked_list;

        for (int i = 0; i < graph_representation[exploring_vertex-1].size_linked_list; i++) {
            
            if (distance_vector[neighboring_vertex->data_int-1] > distance_vector[exploring_vertex-1] + neighboring_vertex->data_float) {
                
                distance_vector[neighboring_vertex->data_int-1] = distance_vector[exploring_vertex-1] + neighboring_vertex->data_float;
                heapgraph.push(make_tuple(distance_vector[neighboring_vertex->data_int-1], neighboring_vertex->data_int-1));

            }
            neighboring_vertex = neighboring_vertex->next_node;
        }
        explored_set.push_back(exploring_vertex);
        tuple<int,float> u = heapgraph.top();
        exploring_vertex = get<0>(u);
        heapgraph.pop();
        
    }

    for(const auto& i: distance_vector) {
        cout << i << endl;
    }

}

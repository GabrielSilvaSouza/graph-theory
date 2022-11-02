import queue
import statistics

def graph_input(file_name):

    with open(file_name) as file_input:
        for line in file_input:
            file_output = line.strip()

    return file_output

def graph_output(graph, representation):

    file_output = open('output.txt', 'w')
    edges = 0

    if representation == 'adjacency_matrix':
        rank_list = [0] * len(graph)
        for vertex in range(len(graph)):
            for neighboring_vertex in range(len(graph[vertex])):
                if graph[vertex][neighboring_vertex] == True:
                    edges += 1
                    rank_list[vertex] += 1

    elif representation == 'adjacency_list':
        rank_list = []
        for vertex in range(len(graph)):
            edges += len(graph[vertex][1])
            rank_list.append(len(graph[vertex][1]))

    rank_list.sort()
    file_output.write('numero de vertices'+ str(len(graph))+'\n'
            +'numero de arestas'+ str(edges//2)+'\n'
            +'grau minimo'+ str(rank_list[0])+'\n'
            +'grau maximo'+ str(rank_list[len(rank_list)-1])+'\n'
            +'grau medio' +str(statistics.mean(rank_list))+'\n'
            +'grau mediano'+ str(statistics.median(rank_list))+'\n')

    return file_output

def graph_builder_adjacency_matrix(file_name):

    with open(file_name) as file_input:
        number_vertex = int(file_input.readline())
        graph = [[False] * number_vertex for vertex in range(number_vertex)]
        for line in file_input:
            vertex_a, vertex_b = line.split()
            vertex_a, vertex_b = int(vertex_a)-1, int(vertex_b)-1
            graph[vertex_a][vertex_b] = graph[vertex_b][vertex_a] = True

    return graph

def graph_builder_adjacency_list(file_name):

    with open(file_name) as file_input:
        number_vertex = int(file_input.readline())
        graph = [[i, []] * 1 for i in range(1, number_vertex+1)]
        for line in file_input:
            vertex, neighboring_vertex = line.split()
            vertex, neighboring_vertex = int(vertex)-1, int(neighboring_vertex)-1
            graph[vertex][1] += [neighboring_vertex+1]
            graph[neighboring_vertex][1] += [vertex+1]

    return graph

def breadth_first_search(graph, root, representation):

    file_output = open('BFS_output.txt', 'w')
    label_list = ['unknown'] * len(graph)
    level_list = [0] * len(graph)
    exploration_queue = queue.Queue()
    label_list[root-1] = 'explored'
    exploration_queue.put(root-1)
    file_output.write('vertice:'+str(root)+' pai:raiz nivel:0'+'\n')
    
    while exploration_queue.empty() != True:
        vertex = exploration_queue.get()
        for neighboring_vertex in range(len(graph)):
            if representation == 'adjacency_matrix':
                if (graph[vertex][neighboring_vertex] == True) and (label_list[neighboring_vertex] == 'unknown'):
                    label_list[neighboring_vertex] = 'discovered'
                    level_list[neighboring_vertex] = level_list[vertex]+1
                    exploration_queue.put(neighboring_vertex)
                    file_output.write('vertice:'+str(neighboring_vertex+1)+' pai:'+str(vertex+1)+' nivel:'+str(level_list[neighboring_vertex])+'\n')

            elif representation == 'adjacency_list':
                if (neighboring_vertex+1 in graph[vertex][1]) and (label_list[neighboring_vertex] == 'unknown'):
                    label_list[neighboring_vertex] = 'discovered'
                    level_list[neighboring_vertex] = level_list[vertex]+1
                    exploration_queue.put(neighboring_vertex)
                    file_output.write('vertice:'+str(neighboring_vertex+1)+' pai:'+str(vertex+1)+' nivel:'+str(level_list[neighboring_vertex])+'\n')

    return file_output

def depth_first_search(graph, root, representation):

    file_output = open('DFS_output.txt', 'w')
    label_list = ['unknown'] * len(graph)
    level_list = [0] * len(graph)
    exploration_stack = [root-1]
    file_output.write('vertice:'+str(root)+' pai:raiz nivel:0'+'\n')

    if representation == 'adjacency_matrix':
        while exploration_stack != []:
            vertex = exploration_stack.pop()
            if (label_list[vertex] != 'discovered'):
                label_list[vertex] = 'discovered'
                for neighboring_vertex in range(len(graph[vertex])):
                    if (graph[vertex][neighboring_vertex] == True):
                        level_list[neighboring_vertex] = level_list[vertex]+1
                        exploration_stack += [neighboring_vertex]
                        file_output.write('vertice:'+str(neighboring_vertex+1)+' pai:'+str(neighboring_vertex+1)+' nivel:'+str(level_list[neighboring_vertex])+'\n')

    elif representation == 'adjacency_list':
        while exploration_stack != []:
            vertex = exploration_stack.pop()
            if (label_list[vertex] != 'discovered'):
                label_list[vertex] = 'discovered'
                for neighboring_vertex in range(len(graph)):
                    if (neighboring_vertex+1 in graph[vertex][1]):
                        level_list[neighboring_vertex] = level_list[vertex]+1
                        exploration_stack += [neighboring_vertex]
                        file_output.write('vertice:'+str(neighboring_vertex+1)+' pai:'+str(vertex+1)+' nivel:'+str(level_list[neighboring_vertex])+'\n')

    return file_output

def get_distance(graph, root, destiny, representation):

    label_list = ['unknown'] * len(graph)
    level_list = [0] * len(graph)
    exploration_queue = queue.Queue()
    label_list[root-1] = 'explored'
    exploration_queue.put(root-1)

    if representation == 'adjacency_matrix':
        while exploration_queue.empty() != True:
            vertex = exploration_queue.get()
            for neighboring_vertex in range(len(graph[vertex])):
                if (graph[vertex][neighboring_vertex] == True) and (label_list[neighboring_vertex] == 'unknown'):
                    label_list[neighboring_vertex] = 'discovered'
                    level_list[neighboring_vertex] = level_list[vertex]+1
                    exploration_queue.put(neighboring_vertex)

    elif representation == 'adjacency_list':
        while exploration_queue.empty() != True:
            vertex = exploration_queue.get()
            for neighboring_vertex in range(len(graph)):
                if (neighboring_vertex+1 in graph[vertex][1]) and (label_list[neighboring_vertex] == 'unknown'):
                    label_list[neighboring_vertex] = 'discovered'
                    level_list[neighboring_vertex] = level_list[vertex]+1
                    exploration_queue.put(neighboring_vertex)

    try:
        distance = level_list[destiny-1]-1
    except:
        distance = -1
    
    if distance == -1: return -1
    else: return distance

def get_diameter(graph, representation):

    diameter = -1

    if representation == 'adjacency_matrix':
        for vertex in range(len(graph)):
            for neighboring_vertex in range(vertex, len(graph)):
                if vertex == neighboring_vertex:
                    pass
                else: 
                    temporary_distance = get_distance(graph, vertex, neighboring_vertex, 'adjacency_matrix')
                    if temporary_distance > diameter: diameter = temporary_distance

    elif representation == 'adjacency_list':
        for vertex in range(len(graph)):
            for neighboring_vertex in range(vertex, len(graph)):
                if vertex == neighboring_vertex:
                    pass
                else: 
                    temporary_distance = get_distance(graph, vertex, neighboring_vertex, 'adjacency_list')
                    if  temporary_distance > diameter: diameter = temporary_distance

    return diameter

def get_connected_component(graph, representation):

    label_list = ['unknown'] * len(graph)
    level_list = [0] * len(graph)
    exploration_queue = queue.Queue()
    connected_component_elements_list = []

    while ('unknown' in label_list):

        next_vertex = label_list.index('unknown')
        label_list[next_vertex] = 'explored'
        exploration_queue.put(next_vertex)
        connected_component_elements_list.append([next_vertex+1])

        if representation == 'adjacency_matrix':
            while exploration_queue.empty() != True:
                vertex = exploration_queue.get()
                for neighboring_vertex in range(len(graph[vertex])):
                    if (graph[vertex][neighboring_vertex] == True) and (label_list[neighboring_vertex] == 'unknown'):
                        label_list[neighboring_vertex] = 'discovered'
                        level_list[neighboring_vertex] = level_list[vertex]+1 
                        exploration_queue.put(neighboring_vertex)
                        connected_component_elements_list[len(connected_component_elements_list)-1].append(neighboring_vertex+1)

        elif representation == 'adjacency_list':
            while exploration_queue.empty() != True:
                vertex = exploration_queue.get()
                for neighboring_vertex in range(len(graph)):
                    if (neighboring_vertex+1 in graph[vertex][1]) and (label_list[neighboring_vertex] == 'unknown'):
                        label_list[neighboring_vertex] = 'discovered'
                        level_list[neighboring_vertex] = level_list[vertex]+1
                        exploration_queue.put(neighboring_vertex)
                        connected_component_elements_list[len(connected_component_elements_list)-1].append(neighboring_vertex+1)

    connected_component_elements_list.sort(key=len)
    connected_component_length_list = []
    for neighboring_vertex in range(len(connected_component_elements_list)): connected_component_length_list.append(len(connected_component_elements_list[neighboring_vertex]))

    return (len(connected_component_elements_list), connected_component_length_list, connected_component_elements_list)

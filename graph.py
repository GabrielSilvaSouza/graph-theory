def graphInput():
    with open(r'c:\Users\lucas\Downloads\example.txt') as f:
        for line in f:
            print(line.strip())
    return

def graphOutput():
    return

def graphBuilderAdjacencyMatrix():

    with open(r'c:\Users\lucas\Downloads\example.txt') as f:
        numberVertex = int(f.readline())
        graph = [[False] * numberVertex for i in range(numberVertex)]
        for line in f:
            Vertex_a, Vertex_b = line.split()
            Vertex_a, Vertex_b = int(Vertex_a)-1, int(Vertex_b)-1
            graph[Vertex_a][Vertex_b] = graph[Vertex_b][Vertex_a] = True

    return graph

def graphBuilderAdjacencyList():

    with open(r'c:\Users\lucas\Downloads\example.txt') as f:
        numberVertex = int(f.readline())
        graph = [[i, []] * 1 for i in range(1, numberVertex+1)]
        for line in f:
            Vertex_a, Vertex_b = line.split()
            Vertex_a, Vertex_b = int(Vertex_a)-1, int(Vertex_b)-1
            graph[Vertex_a][1] += [Vertex_b+1]
            graph[Vertex_b][1] += [Vertex_a+1]

    return graph

def breadthFirstSearch(startVertex):



    return

def depthFirstSearch():
    return

def findDistance():
    return

def findDiameter():
    return

def findConnectedComponent():
    return

print(graphBuilderAdjacencyList())
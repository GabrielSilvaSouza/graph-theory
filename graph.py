import queue

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
            vertex_a, vertex_b = line.split()
            vertex_a, vertex_b = int(vertex_a)-1, int(vertex_b)-1
            graph[vertex_a][vertex_b] = graph[vertex_b][vertex_a] = True

    return graph

def graphBuilderAdjacencyList():

    with open(r'c:\Users\lucas\Downloads\example.txt') as f:
        numberVertex = int(f.readline())
        graph = [[i, []] * 1 for i in range(1, numberVertex+1)]
        for line in f:
            vertex_a, vertex_b = line.split()
            vertex_a, vertex_b = int(vertex_a)-1, int(vertex_b)-1
            graph[vertex_a][1] += [vertex_b+1]
            graph[vertex_b][1] += [vertex_a+1]

    return graph

def breadthFirstSearch(graph, root, representation):

    f = open('BFSoutput.txt', 'w')
    labelList = ['unknown'] * len(graph)
    levelList = [0] * len(graph)
    Q = queue.Queue()
    labelList[root-1] = 'explored'
    Q.put(root-1)
    f.write('vertice:'+str(root)+' pai:raiz nivel:0')
    f.write('\n')

    if representation == 'AdjacencyMatrix':
        while Q.empty() != True:
            v = Q.get()
            for i in range(len(graph[v])):
                if (graph[v][i] == True) and (labelList[i] == 'unknown'):
                    labelList[i] = 'discovered'
                    levelList[i] = levelList[v]+1 
                    Q.put(i)
                    f.write('vertice:'+str(i+1)+' pai:'+str(v+1)+' nivel:'+str(levelList[i]))
                    f.write('\n')

    elif representation == 'AdjacencyList':
        while Q.empty() != True:
            v = Q.get()
            for i in range(len(graph)):
                if (i+1 in graph[v][1]) and (labelList[i] == 'unknown'):
                    labelList[i] = 'discovered'
                    levelList[i] = levelList[v]+1
                    Q.put(i)
                    f.write('vertice:'+str(i+1)+' pai:'+str(v+1)+' nivel:'+str(levelList[i]))
                    f.write('\n')

    return f

def depthFirstSearch(graph, root, representation):

    f = open('DFSoutput.txt', 'w')
    labelList = ['unknown'] * len(graph)
    levelList = [0] * len(graph)
    S = [root-1]
    f.write('vertice:'+str(root)+' pai:raiz nivel:0')
    f.write('\n')

    if representation == 'AdjacencyMatrix':
        while S != []:
            v = S.pop()
            if (labelList[v] != 'discovered'):
                labelList[v] = 'discovered'
                for i in range(len(graph[v])):
                    if (graph[v][i] == True):
                        levelList[i] = levelList[v]+1
                        S += [i]
                        f.write('vertice:'+str(i+1)+' pai:'+str(v+1)+' nivel:'+str(levelList[i]))
                        f.write('\n')

    elif representation == 'AdjacencyList':
        while S != []:
            v = S.pop()
            if (labelList[v] != 'discovered'):
                labelList[v] = 'discovered'
                for i in range(len(graph)):
                    if (i+1 in graph[v][1]):
                        S += [i]
                        if ():
                            levelList[i] = levelList[v]+1
                            f.write('vertice:'+str(i+1)+' pai:'+str(v+1)+' nivel:'+str(levelList[i]))
                            f.write('\n')

    return f

def findDistance():
    return

def findDiameter():
    return

def findConnectedComponent():
    return

test = graphBuilderAdjacencyMatrix()
print(test)
depthFirstSearch(test, 1, 'AdjacencyMatrix')

import queue
import statistics

def graphInput(file_name):
    with open(file_name) as f:
        for line in f:
            print(line.strip())
    return

def graphOutput(graph, representation):

    f = open('output.txt', 'w')
    edges = 0
    if representation == 'AdjacencyMatrix':
        rankList = [0] * len(graph)
        for i in range(len(graph)):
            for j in range(len(graph[i])):
                if graph[i][j] == True:
                    edges += 1
                    rankList[i] += 1

    elif representation == 'AdjacencyList':
        rankList = []
        for i in range(len(graph)):        
            edges += len(graph[i][1])
            rankList.append(len(graph[i][1]))

    rankList.sort()
    f.write('numero de vertices'+ str(len(graph))+'\n'
            +'numero de arestas'+ str(edges//2)+'\n'
            +'grau minimo'+ str(rankList[0])+'\n'
            +'grau maximo'+ str(rankList[len(rankList)-1])+'\n'
            +'grau medio' +str(statistics.mean(rankList))+'\n'
            +'grau mediano'+ str(statistics.median(rankList))+'\n')

    return f

def graphBuilderAdjacencyMatrix(file_name):

    with open(file_name) as f:
        numberVertex = int(f.readline())
        graph = [[False] * numberVertex for i in range(numberVertex)]
        for line in f:
            vertex_a, vertex_b = line.split()
            vertex_a, vertex_b = int(vertex_a)-1, int(vertex_b)-1
            graph[vertex_a][vertex_b] = graph[vertex_b][vertex_a] = True

    return graph

def graphBuilderAdjacencyList(file_name):

    with open(file_name) as f:
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
    f.write('vertice:'+str(root)+' pai:raiz nivel:0'+'\n')
    
    while Q.empty() != True:
        v = Q.get()
        for i in range(len(graph[v])):
            if representation == 'AdjacencyMatrix':
                if (graph[v][i] == True) and (labelList[i] == 'unknown'):
                    labelList[i] = 'discovered'
                    levelList[i] = levelList[v]+1
                    Q.put(i)
                    f.write('vertice:'+str(i+1)+' pai:'+str(v+1)+' nivel:'+str(levelList[i])+'\n')

            elif representation == 'AdjacencyList':
                if (i+1 in graph[v][1]) and (labelList[i] == 'unknown'):
                    labelList[i] = 'discovered'
                    levelList[i] = levelList[v]+1
                    Q.put(i)
                    f.write('vertice:'+str(i+1)+' pai:'+str(v+1)+' nivel:'+str(levelList[i])+'\n')

    return f

def depthFirstSearch(graph, root, representation):

    f = open('DFSoutput.txt', 'w')
    labelList = ['unknown'] * len(graph)
    levelList = [0] * len(graph)
    S = [root-1]
    f.write('vertice:'+str(root)+' pai:raiz nivel:0'+'\n')

    if representation == 'AdjacencyMatrix':
        while S != []:
            v = S.pop()
            if (labelList[v] != 'discovered'):
                labelList[v] = 'discovered'
                for i in range(len(graph[v])):
                    if (graph[v][i] == True):
                        levelList[i] = levelList[v]+1
                        S += [i]
                        f.write('vertice:'+str(i+1)+' pai:'+str(v+1)+' nivel:'+str(levelList[i])+'\n')

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
                            f.write('vertice:'+str(i+1)+' pai:'+str(v+1)+' nivel:'+str(levelList[i])+'\n')

    return f

def findDistance(graph, root, destiny, representation):

    labelList = ['unknown'] * len(graph)
    levelList = [0] * len(graph)
    Q = queue.Queue()
    labelList[root-1] = 'explored'
    Q.put(root-1)

    if representation == 'AdjacencyMatrix':
        while Q.empty() != True:
            v = Q.get()
            for i in range(len(graph[v])):
                if (graph[v][i] == True) and (labelList[i] == 'unknown'):
                    labelList[i] = 'discovered'
                    levelList[i] = levelList[v]+1
                    Q.put(i)

    elif representation == 'AdjacencyList':
        while Q.empty() != True:
            v = Q.get()
            for i in range(len(graph)):
                if (i+1 in graph[v][1]) and (labelList[i] == 'unknown'):
                    labelList[i] = 'discovered'
                    levelList[i] = levelList[v]+1
                    Q.put(i)

    try:
        distance = levelList[destiny-1]-1
    except:
        distance = -1
    if distance == -1: return -1
    else: return distance

def findDiameter(graph, representation):

    diameter = -1

    if representation == 'AdjacencyMatrix':
        for i in range(len(graph)):
            for j in range(i, len(graph)):
                if i == j:
                    ''
                else: 
                    tempDistance = findDistance(graph, i, j, 'AdjacencyMatrix')
                    if  tempDistance > diameter: diameter = tempDistance

    elif representation == 'AdjacencyList':
        for i in range(len(graph)):
            for j in range(i, len(graph)):
                if i == j:
                    ''
                else: 
                    tempDistance = findDistance(graph, i, j, 'AdjacencyList')
                    if  tempDistance > diameter: diameter = tempDistance

    return diameter

def findConnectedComponent(graph, representation):

    labelList = ['unknown'] * len(graph)
    levelList = [0] * len(graph)
    Q = queue.Queue()
    connectedComponentElementsList = []

    while ('unknown' in labelList):

        nextVertex = labelList.index('unknown')
        labelList[nextVertex] = 'explored'
        Q.put(nextVertex)
        connectedComponentElementsList.append([nextVertex+1])
        if representation == 'AdjacencyMatrix':
            while Q.empty() != True:
                v = Q.get()
                for i in range(len(graph[v])):
                    if (graph[v][i] == True) and (labelList[i] == 'unknown'):
                        labelList[i] = 'discovered'
                        levelList[i] = levelList[v]+1 
                        Q.put(i)
                        connectedComponentElementsList[len(connectedComponentElementsList)-1].append(i+1)

        elif representation == 'AdjacencyList':
            while Q.empty() != True:
                v = Q.get()
                for i in range(len(graph)):
                    if (i+1 in graph[v][1]) and (labelList[i] == 'unknown'):
                        labelList[i] = 'discovered'
                        levelList[i] = levelList[v]+1
                        Q.put(i)
                        connectedComponentElementsList[len(connectedComponentElementsList)-1].append(i+1)

    connectedComponentElementsList.sort(key=len)
    connectedComponentLengthList = []
    for i in range(len(connectedComponentElementsList)):
        connectedComponentLengthList.append(len(connectedComponentElementsList[i]))

    return (len(connectedComponentElementsList), connectedComponentLengthList, connectedComponentElementsList)

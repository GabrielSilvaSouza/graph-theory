import queue

class NodeLinked(object):
    def __init__(self, vertex):
        self.vertex = vertex
        self.sucessor = None

class Linked(object):

    def __init__(self):
        self.head = None

    def go(self,v):
        p = NodeLinked(v)
            
        f = self.head   
        while (f.sucessor): #find a free slot 
            f = f.sucessor
            
        f.sucessor = p

    def printl(self):
        k = self.head
        if k is None:
            pass
        else:
            print(k.vertex)
            while k.sucessor is not None:
                k = k.sucessor
                print("---> ", k.vertex)

    def runner(self):
        f = self.head   
        while (f.sucessor): 
            f = f.sucessor


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
    with open(r'/home/mrunknown/grafo_2.txt') as f:
        numberVertex = int(f.readline())
        graph = [Linked() for i in range(1,numberVertex+2)]

        for line in f:
            vertex_a, vertex_b = line.split()
            vertex_a, vertex_b = int(vertex_a), int(vertex_b)
            new_node_1 = NodeLinked(vertex_a)
            new_node_2 = NodeLinked(vertex_b)
            if graph[new_node_1.vertex].head is None:
                graph[new_node_1.vertex].head = new_node_1
                graph[new_node_1.vertex].go(vertex_b) 

            else:
                    graph[new_node_1.vertex].go(vertex_b)

            if graph[new_node_2.vertex].head is None:
                graph[new_node_2.vertex].head = new_node_2
                graph[new_node_2.vertex].go(vertex_a) 

            else:
                graph[new_node_2.vertex].go(vertex_a)

                    

    for i in range(0, len(graph)):
                graph[i].printl()

    return graph

def breadthFirstSearch(graph, root, representation):

    f = open('BFSoutput.txt', 'w')
    labelList = ['unknown'] * len(graph)
    levelList = [0] * len(graph)
    Q = []
    labelList[root] = 'explored'
    Q.append(graph[root].head.vertex)         

    if representation == 'AdjacencyList':
        
        while len(Q) != 0:
            v = Q.pop()
            for i in range(1,len(graph)): #tirar isso depois e substituir por uma variavel contável

                while graph[i].head.sucessor:
                    print(labelList[graph[i].head.sucessor.vertex])
                    if (labelList[graph[i].head.sucessor.vertex] == 'unknown'):
                        labelList[graph[i].head.sucessor.vertex] = 'discovered'
                        levelList[graph[i].head.sucessor.vertex] = levelList[v]+1
                        Q.append(graph[i])
                    else:
                        break
        f.write('vertice:'+str(i)+' pai:'+str(v.head.vertex)+' nivel:'+str(levelList[root]))
        f.write('\n')

    return f

def depthFirstSearch(graph, root, representation):

    f = open('DFSoutput.txt', 'w')
    labelList = ['unknown'] * len(graph)
    levelList = [0] * len(graph)
    S = [graph[root].head.vertex]
    f.write('vertice:'+str(root)+' pai:raiz nivel:0')
    f.write('\n')

    if representation == 'AdjacencyList':
        while S != []:
            v = S.pop()
            if (labelList[v] != 'discovered'):
                labelList[v] = 'discovered'
                for i in range(1, len(graph)):
                    while graph[i].head.sucessor:
                        S += [graph[i].head.sucessor.vertex]
                        if ():
                            levelList[i] = levelList[v]+1
                            print(levelList)
                            f.write('vertice:'+str(i+1)+' pai:'+str(v+1)+' nivel:'+str(levelList[i]))
                            f.write('\n')
                        else:
                            break
    
    return f

def getDistance(graph, root, destination, representation):

    labelList = ['unknown'] * len(graph)
    levelList = [0] * len(graph)
    Q = []
    labelList[root] = 'explored'
    Q.append(graph[root].head.vertex)         

    if representation == 'AdjacencyList':
        c = 0
        while len(Q) != 0:
            v = Q.pop()
            for i in range(1,len(graph)):
                while graph[i].head.sucessor:
                    if i == root:
                        if (labelList[graph[i].head.sucessor.vertex] == 'unknown'):
                            labelList[graph[i].head.sucessor.vertex] = 'discovered'
                            levelList[graph[i].head.sucessor.vertex] = levelList[v]+1
                            Q.append(graph[i])
                        else:
                            break

    print(levelList)                   

    return None                        


if __name__ == "__main__":
    #graphBuilderAdjacencyMatrix()
    u = graphBuilderAdjacencyList()
    #breadthFirstSearch(u,2,'AdjacencyList')
    #depthFirstSearch(u, 2, 'AdjacencyList')
    #getDistance(u,2,4,'AdjacencyList')




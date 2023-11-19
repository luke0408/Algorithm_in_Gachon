class Node:

    def __init__(self, idx, data=0):  # Constructor
        """
        id : Integer (1, 2, 3, ...)
        """
        self.id = idx
        self.data = data
        self.connectedTo = dict()

    def addNeighbour(self, neighbour, weight=0):
        """
        neighbour : Node Object
        weight : Default Value = 0

        adds the neightbour_id : wt pair into the dictionary
        """
        if neighbour.id not in self.connectedTo.keys():
            self.connectedTo[neighbour.id] = weight

    # getter
    def getConnections(self):
        return self.connectedTo.keys()

    def getID(self):
        return self.id


class Graph:
    totalV = 0  # total vertices in the graph

    def __init__(self):
        """
        allNodes = Dictionary (key:value)
                   idx : Node Object
        """
        self.allNodes = dict()

    def addNode(self, idx):
        """ adds the node """
        if idx in self.allNodes:
            return None

        Graph.totalV += 1
        node = Node(idx=idx)
        self.allNodes[idx] = node
        return node

    def addEdge(self, src, dst, wt=0):
        """
        Adds edge between 2 nodes
        Undirected graph

        src = node_id = edge starts from
        dst = node_id = edge ends at

        To make it a directed graph comment the second line
        """
        self.allNodes[src].addNeighbour(self.allNodes[dst], wt)
        self.allNodes[dst].addNeighbour(self.allNodes[src], wt)

    def isNeighbour(self, u, v):
        """
        check neighbour exists or not
        """
        if u >= 1 and u <= 81 and v >= 1 and v <= 81 and u != v:
            if v in self.allNodes[u].getConnections():
                return True
        return False

    def getAllNodesIds(self):
        return self.allNodes.keys()


    def __DFSUtility(self, node_id, visited):
        visited = self.__setVisitedTrue(visited=visited, node_id=node_id)
        # print
        print(self.allNodes[node_id].getID(), end=" ")

        # Recursive Stack
        for i in self.allNodes[node_id].getConnections():
            if visited[self.allNodes[i].getID()] == False:
                self.__DFSUtility(node_id=self.allNodes[i].getID(),
                                  visited=visited)

    def __setVisitedTrue(self, visited, node_id):
        """
        Utility function for BFS and DFS

        Through this function we will set visited[id] = True
        Preprocessing node_id if required
        Since now node_id is an integer it is not required to preprocess it
        """
        visited[node_id] = True
        return visited
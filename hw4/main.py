from sys import argv
import queue
import graphviz

class Graph:
    # make graph from num edges
    def __init__( self, v, e ):
        self.size = len(v)
        self.vertices = e
        self.parent = { v0: -1 for v0 in v }
        self.can_reach = set()

    # bfs for Edmonds-Karp, checks if source can reach terminal
    def bfs( self, source, terminal ):
        visited = [ False for _ in range(self.size) ]
        q = queue.Queue()
        q.put(source)
        visited[source] = True

        # iterate through queue until we find terminal node
        while not q.empty():
            curr_node = q.get()
            for v, _ in self.vertices[curr_node].items():
                if not visited[v]:
                    q.put(v)
                    visited[v] = True
                    # parent of v is current node
                    self.parent[v] = curr_node
                    if v == terminal:
                        return True
        # cannot reach terminal node, return
        return False

    # finds reachable nodes from current node
    def find_reachable( self, v0 ):
        self.can_reach.add( v0 )
        for v, _ in self.vertices[v0].items():
            if v not in self.can_reach:
                self.find_reachable( v )

    def edmonds_karp( self, source, terminal ):
        max_flow = 0
        
        while self.bfs( source, terminal ):
            # iterate backwards to source node
            v = terminal
            if v != source:
                path_flow = self.vertices[self.parent[v]][v]
                v = self.parent[v]
                while v != source:
                    # find min path flow
                    path_flow = min( path_flow, self.vertices[self.parent[v]][v] )
                    v = self.parent[v]

            # add min path flow to total
            max_flow += path_flow

            # reverse the flow
            v1 = terminal
            while v1 != source:
                v0 = self.parent[v1]
                if self.vertices[v0][v1] == path_flow:
                    del self.vertices[v0][v1]
                else:
                    self.vertices[v0][v1] -= path_flow
                if v1 not in self.vertices:
                    self.vertices.update( {v1: {}} )
                if v0 not in self.vertices[v1]:
                    self.vertices[v1].update( {v0: path_flow} )
                else:
                    self.vertices[v1][v0] += path_flow
                v1 = v0
            # update reachable node from source
            self.can_reach = set()
            self.find_reachable( source )

        return max_flow

    # prints graph using graphviz library
    def print_graph( self, output_file ):
        output = graphviz.Digraph( comment="Flow" )
        for i, e in self.vertices.items():
            for j, c in e.items():
                output.edge( str(i), str(j), label=str(c) )
        output.render( output_file, format="png" )

with open( argv[1], "r" ) as input:
    vertices = set()
    edges = {}
    # parse for dictionary of edges
    # ex: { 0: {1:20, 2:10}, 1: {2: 20, 3, 10}, 2: {3: 20} }
    for line in input:
        if '->' in line:
            line = line.split( '->' )
            curr_node = int(line[0].split()[0])
            vertices.add( curr_node )
            if curr_node not in edges:
                edges.update( {curr_node: {}} )
            
            half = line[1]
            half = half.split("\"")
            edge_node = int(half[0].split()[0])
            vertices.add( edge_node )
            capacity = int(half[-2])
            edges[curr_node].update( {edge_node: capacity} )

    graph = Graph( vertices, edges )

    flow = graph.edmonds_karp( 0, graph.size-1 )
    print( f'Max Flow: {flow}' )

    cut = graph.can_reach
    print( f'Cut: {cut}' )

    graph.print_graph( 'output' )

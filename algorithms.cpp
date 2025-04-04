// dor.cohen15@msmail.ariel.ac.il


#include "graph.hpp"
using namespace graph;

namespace graph{
    

// ============================
//         BFS SECTION
// ============================

    /**
     * @brief Performs BFS traversal and builds a BFS tree.
     * 
     * Traverses the given graph from a start vertex using Breadth-First Search,
     * and returns a new graph containing only the tree edges from the traversal.
     * 
     * @param g The original graph.
     * @param start The starting vertex for BFS.
     * @return Graph The BFS tree rooted at 'start'.
     */
    Graph Algorithms::bfs(Graph& g, int start){
        if (start < 0 || start >= g.getNumVertices()) {
            throw std::out_of_range("Invalid start vertex in BFS");
        }
        Graph bfsTree(g.getNumVertices());
        bool* visited = new bool[g.getNumVertices()];
        for (int i = 0; i < g.getNumVertices(); ++i) {
        visited[i] = false;
        }
        Node** adjList = g.getAdjList();
        Queue queue(g.getNumVertices());
        visited[start]= true;
        queue.enqueue(start);

        while (!queue.isEmpty())
        {
            int current=queue.dequeue();
            Node* neighbor = adjList[current];
            while (neighbor != nullptr) {
                int v = neighbor->vertex;
                if (!visited[v]){
                    visited[v]=true;
                    bfsTree.addDirectedEdge(current,v,neighbor->weight);
                    queue.enqueue(v);
                }
                neighbor= neighbor->next;
            }
        }
        delete[] visited;
        return bfsTree;
    }


// ============================
//         DFS SECTION
// ============================

    /**
     * @brief Performs DFS traversal and builds a DFS tree.
     * 
     * Traverses the given graph from a start vertex using Depth-First Search,
     * and returns a new graph containing only the tree edges from the traversal.
     * 
     * @param g The original graph.
     * @param start The starting vertex for DFS.
     * @return Graph The DFS tree rooted at 'start'.
     */
    Graph Algorithms::dfs(Graph& g, int start) {
        if (start < 0 || start >= g.getNumVertices()) {
            throw std::out_of_range("Invalid start vertex in DFS");
        }
        int vertexNum = g.getNumVertices();
        Graph dfsTree(vertexNum);
    
        bool* visited = new bool[vertexNum];
        for (int i = 0; i < vertexNum; ++i)
            visited[i] = false;
    
        Node** adjList = g.getAdjList();
        Stack stack(vertexNum);
    
        stack.push(start);
        visited[start] = true;  // ⭐ סימון ברגע שדוחפים
    
        while (!stack.isEmpty()) {
            int current = stack.pop();
            if (current == 2147483647 || current < 0 || current >= vertexNum)
                continue;
    
            Node* neighbor = adjList[current];
            while (neighbor != nullptr) {
                int v = neighbor->vertex;
    
                if (v >= 0 && v < vertexNum && !visited[v]) {
                    visited[v] = true;  // ⭐ מונע דחיפה כפולה
                    dfsTree.addDirectedEdge(current, v, neighbor->weight);
                    stack.push(v);
                }
    
                neighbor = neighbor->next;
            }
        }
    
        delete[] visited;
        return dfsTree;
    }

// ============================
//         DIJKSTRA SECTION
// ============================
    /**
     * @brief Performs the relaxation step of Dijkstra's algorithm.
     *        If the path from u to v through the current edge (u → v)
     *        provides a shorter distance, updates the distance and parent.
     *        Also updates the priority queue with the new distance.
     * 
     * @param u The current vertex being processed.
     * @param v The neighbor vertex connected to u.
     * @param weight The weight of the edge (u → v).
     * @param distances Array of current shortest distances from the source vertex.
     * @param parent Array holding the previous vertex on the shortest path to each node.
     * @param pq Priority queue used to select the next vertex to process.
     */
    void Algorithms::relax(int u, int v, int weight, int* distances, int* parent, PriorityQueue& pq) {
        if (distances[u] + weight < distances[v]) {
            distances[v] = distances[u] + weight;
            parent[v] = u;
            pq.insert(v, distances[v]); 
        }
    }

    /**
     * @brief Computes the shortest paths from a start vertex to all other vertices using Dijkstra's algorithm.
     *        The result is returned as a directed tree (shortest path tree), where each edge represents the 
     *        shortest path from the parent to the child.
     * 
     * @param g The input graph (undirected, with positive edge weights).
     * @param start The starting vertex to run the algorithm from.
     * @return Graph The shortest-path tree as a directed graph.
     * 
     * @throws std::out_of_range If the start vertex is not within the valid range.
     */
    Graph Algorithms::dijkstra(Graph& g, int start) {
        if (start < 0 || start >= g.getNumVertices()) {
            throw std::out_of_range("Invalid start vertex in DIJKSTRA");
        }
        int vertexNum = g.getNumVertices();
        int* distances = new int[vertexNum];
        int* parent = new int[vertexNum];
        bool* visited = new bool[vertexNum];
    
        for (int i = 0; i < vertexNum; i++) {
            distances[i] = 2147483647;
            parent[i] = -1;
            visited[i] = false;
        }
    
        distances[start] = 0;
    
        PriorityQueue pq(vertexNum);
        pq.insert(start, 0);
    
        while (!pq.isEmpty()) {
            int u = pq.extractMin();
            if (visited[u]) continue;
            visited[u] = true;
    
            Node* neighbor = g.getAdjList()[u];
            while (neighbor != nullptr) {
                int v = neighbor->vertex;
                int weight = neighbor->weight;
    
                relax(u, v, weight, distances, parent, pq); 
    
                neighbor = neighbor->next;
            }
        }
        
        Graph shortestTree(vertexNum);
        for (int i = 0; i < vertexNum; i++) {
            if (parent[i] != -1) {
                int weight = distances[i] - distances[parent[i]];
                shortestTree.addDirectedEdge(parent[i], i, weight);
            }
        }
    
        delete[] distances;
        delete[] parent;
        delete[] visited;
    
        return shortestTree;
    }

// ============================
//         PRIM SECTION
// ============================
    /**
     * @brief Computes the Minimum Spanning Tree (MST) of a graph using Prim's algorithm.
     *        The function assumes that the graph is connected (or will compute the MST of the connected component
     *        starting from vertex 0). The result is returned as an undirected graph representing the MST.
     * 
     * @param g The input graph (undirected, weighted).
     * @return Graph The resulting MST as an undirected graph.
     */
    Graph Algorithms::prim(Graph& g) {
        int V = g.getNumVertices();
        Graph mst(V);
        bool* visited = new bool[V];
        int* parent = new int[V];
        int* key = new int[V];
    
        for (int i = 0; i < V; i++) {
            visited[i] = false;
            key[i] = 2147483647;
            parent[i] = -1;
        }
    
        key[0] = 0;
        PriorityQueue pq(V);
        pq.insert(0, 0);
    
        while (!pq.isEmpty()) {
            int u = pq.extractMin();
            visited[u] = true;
    
            Node* neighbor = g.getAdjList()[u];
            while (neighbor != nullptr) {
                int v = neighbor->vertex;
                int weight = neighbor->weight;
    
                if (!visited[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    pq.insert(v, key[v]);
                }
    
                neighbor = neighbor->next;
            }
        }
    
        for (int v = 1; v < V; v++) {
            if (parent[v] != -1) {
                int weight = key[v];
                mst.addEdge(parent[v], v, weight); 
            }
        }
    
        delete[] visited;
        delete[] parent;
        delete[] key;
    
        return mst;
    }


// ============================
//       KRUSKAL SECTION
// ============================
    /**
     * @brief Computes the Minimum Spanning Tree (MST) of the input graph using Kruskal's algorithm.
     *        The algorithm sorts all edges by weight and adds the smallest ones to the MST,
     *        as long as they do not form a cycle (using Union-Find to track connected components).
     * 
     * @param g The input graph (undirected, weighted).
     * @return Graph The resulting MST as an undirected graph.
     */
    Graph Algorithms::kruskal(Graph& g) {
        int V = g.getNumVertices();
        Edge* edges = new Edge[V * V];
        int edgeCount = 0;
        Node** adjList = g.getAdjList();

        for (int u = 0; u < V; u++) {
            Node* neighbor = adjList[u];
            while (neighbor != nullptr) {
                int v = neighbor->vertex;
                int w = neighbor->weight;
                if (u < v) {
                    edges[edgeCount++] = {u, v, w};
                }
                neighbor = neighbor->next;
            }
        }

        // Selection sort
        for (int i = 0; i < edgeCount - 1; ++i) {
            int minIdx = i;
            for (int j = i + 1; j < edgeCount; ++j) {
                if (edges[j].weight < edges[minIdx].weight) {
                    minIdx = j;
                }
            }
            if (minIdx != i) {
                Edge temp = edges[i];
                edges[i] = edges[minIdx];
                edges[minIdx] = temp;
            }
        }

        Graph mst(V);
        graph::UnionFind uf(V); 

        for (int i = 0; i < edgeCount; ++i) {
            Edge e = edges[i];
            int uSet = uf.find(e.src);
            int vSet = uf.find(e.dst);

            if (uSet != vSet) {
                mst.addEdge(e.src, e.dst, e.weight);
                uf.unite(uSet, vSet);
            }
        }

        delete[] edges;
        return mst;

        }
}
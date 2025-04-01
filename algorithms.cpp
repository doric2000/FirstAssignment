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

    void Algorithms::relax(int u, int v, int weight, int* distances, int* parent, PriorityQueue& pq) {
        if (distances[u] + weight < distances[v]) {
            distances[v] = distances[u] + weight;
            parent[v] = u;
            pq.insert(v, distances[v]); 
        }
    }

    Graph Algorithms::dijkstra(Graph& g, int start) {
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

    // מיון פשוט לפי משקל (selection sort)
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
    int* parent = new int[V];
    int* rank = new int[V];

    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < edgeCount; ++i) {
        Edge e = edges[i];
        int uSet = graph::find(parent, e.src);
        int vSet = graph::find(parent, e.dst);

        if (uSet != vSet) {
            mst.addEdge(e.src, e.dst, e.weight);
            graph::unionSets(parent, rank, uSet, vSet);
        }
    }

    delete[] parent;
    delete[] rank;
    delete[] edges;

    return mst;
}

}
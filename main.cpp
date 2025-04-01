// dor.cohen15@msmail.ariel.ac.il

#include "graph.hpp"
#include <iostream>
using namespace graph;

void printTitle(const std::string& title) {
    std::cout << "\n=============================\n";
    std::cout << title << "\n";
    std::cout << "=============================\n";
}

int main() {
    Graph g(6);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 3, 7);
    g.addEdge(1, 4, 1);
    g.addEdge(2, 5, 3);
    g.addEdge(3, 5, 1);

    printTitle("Original Graph");
    g.print_graph();

    Graph bfsTree = Algorithms::bfs(g, 0);
    printTitle("BFS Tree (start = 0)");
    bfsTree.print_graph();

    Graph dfsTree = Algorithms::dfs(g, 0);
    printTitle("DFS Tree (start = 0)");
    dfsTree.print_graph();

    Graph dijkstraTree = Algorithms::dijkstra(g, 0);
    printTitle("Dijkstra Tree (start = 0)");
    dijkstraTree.print_graph();

    Graph primTree = Algorithms::prim(g);
    printTitle("Prim MST");
    primTree.print_graph();

    Graph kruskalTree = Algorithms::kruskal(g);
    printTitle("Kruskal MST");
    kruskalTree.print_graph();

    return 0;
}
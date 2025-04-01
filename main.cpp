#include "graph.hpp"
#include <iostream>

using namespace graph;

void printTitle(const std::string& title) {
    std::cout << "\n=============================\n";
    std::cout << title << "\n";
    std::cout << "=============================\n";
}

int main() {
    Graph g(6);  // גרף עם 6 קודקודים

    // גרף עם משקלים שונים כדי לבדוק את דייקסטרה כמו שצריך
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 3, 7);
    g.addEdge(1, 4, 1);
    g.addEdge(2, 5, 3);
    g.addEdge(3, 5, 1);

    printTitle("Original Graph");
    g.print_graph();

    // הרצת BFS
    Graph bfsTree = Algorithms::bfs(g, 0);
    printTitle("BFS Tree (start = 0)");
    bfsTree.print_graph();

    // הרצת DFS
    Graph dfsTree = Algorithms::dfs(g, 0);
    //printTitle("DFS Tree (start = 0)");
    //dfsTree.print_graph();

    // הרצת Dijkstra
    Graph dijkstraTree = Algorithms::dijkstra(g, 0);
    printTitle("Dijkstra Tree (start = 0)");
    dijkstraTree.print_graph();

    return 0;
}
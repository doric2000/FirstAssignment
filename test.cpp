// dor.cohen15@msmail.ariel.ac.il

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "graph.hpp"

using namespace graph;

    
// ============================
//         GRAPH SECTION
// ============================   

TEST_CASE("GRAPH - add2directiones , add1directon , remove") {
    Graph g(5);

    CHECK_NOTHROW(g.addEdge(0, 1, 2));// this func check that there is no exception throw
    CHECK_NOTHROW(g.addEdge(1, 2, 3));
    CHECK_NOTHROW(g.addDirectedEdge(3, 4, 2));

    SUBCASE("ADD an edge") {
        Node** adj = g.getAdjList();
        CHECK(adj[0]->vertex == 1);
        CHECK((adj[1]->vertex == 2 || adj[1]->vertex == 0));  // Either one, because undirected
    }

    SUBCASE("ADD directed edge only") {
        Node** adj = g.getAdjList();
        CHECK(adj[3]->vertex == 4);     // insures that 3-->4 exist
        CHECK(adj[4] == nullptr);       // insures that 4-->3 does not exist
    }

    SUBCASE("ADD an edge that is not in range") {
        CHECK_THROWS(g.addEdge(1, 9, 2));  // 1-->9 not in range
    }

    SUBCASE("ADD a directed edge that is not in range") {
        CHECK_THROWS(g.addDirectedEdge(1, 9, 2));  // 1-->9 not in range
    }

    SUBCASE("REMOVE an edge") {
        CHECK_NOTHROW(g.removeEdge(1, 2));
        Node* n = g.getAdjList()[1];
        while (n != nullptr) {
            CHECK(n->vertex != 2);  // Make sure edge to 2 was removed
            n = n->next;
        }
    }

    SUBCASE("REMOVE a non-existing edge") {
        CHECK_THROWS(g.removeEdge(1, 4));  // 1-->4 not exist
    }

    SUBCASE("REMOVE an edge that is not in range") {
        CHECK_THROWS(g.removeEdge(1, 9));  // 1-->9 not in range
    }

    SUBCASE("removeEdge should remove undirected edge") {
        Graph g(3);
        g.addEdge(0, 1, 5);
        g.removeEdge(0, 1);
    
        Node** adj = g.getAdjList();
    
        // check both sides are gone
        CHECK(adj[0] == nullptr);
        CHECK(adj[1] == nullptr);
    }
    
    SUBCASE("removeEdge should throw if edge does not exist") {
        Graph g(3);
        g.addEdge(0, 1, 5);
        g.removeEdge(0, 1);
        CHECK_THROWS_AS(g.removeEdge(0, 1), std::runtime_error);
    }
    

}

TEST_CASE("GRAPH - print") {
    Graph g(3);
    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, 3);

    std::ostringstream buffer;           // creating an object that will replace :"cout"
    std::streambuf* oldCout = std::cout.rdbuf();  // saving the original cout
    std::cout.rdbuf(buffer.rdbuf());     // changing the cout to write to the buffer

    g.print_graph();                     // what we print will enter to the buffer.

    std::cout.rdbuf(oldCout);            // return cout to normal status

    std::string output = buffer.str();   // get the output to a string

    CHECK(output.find("0 --->") != std::string::npos);  // check the output..
    CHECK(output.find("1 --->") != std::string::npos);
    CHECK(output.find("(1, weight = 2)") != std::string::npos);
    CHECK(output.find("(2, weight = 3)") != std::string::npos);

    SUBCASE("print_graph adjacency list") {
        Graph g(2);
        g.addEdge(0, 1, 7);
    
        std::ostringstream buffer;
        std::streambuf* oldCout = std::cout.rdbuf();
        std::cout.rdbuf(buffer.rdbuf());
    
        g.print_graph();
    
        std::cout.rdbuf(oldCout); // restore cout
    
        std::string output = buffer.str();
        CHECK(output.find("0 --->") != std::string::npos);
        CHECK(output.find("(1, weight = 7)") != std::string::npos);
        CHECK(output.find("1 --->") != std::string::npos);
        CHECK(output.find("(0, weight = 7)") != std::string::npos);
    }
}

// ============================
//         NODE SECTION
// ============================   

TEST_CASE("NODE") {

    SUBCASE("Create a new node") {
        Node n(3, 5);
        CHECK(n.vertex == 3);
        CHECK(n.weight == 5);
        CHECK(n.next == nullptr);
    }
    SUBCASE("Create a new node") {
        Node n1(1,4);
        Node n2(2,5);
        n1.next = &n2;
        CHECK(n1.next->vertex == 2);
        CHECK(n1.next->weight == 5);
    }
    
    SUBCASE("Check node behavior in a graph") {
        Graph g(3);
        g.addEdge(0, 1, 9);

        Node** adj = g.getAdjList();
        CHECK(adj[0]->vertex == 1);
        CHECK(adj[0]->weight == 9);
    }
}

// ============================
//         QUEUE SECTION
// ============================   

TEST_CASE("QUEUE - enqueue, dequeue, circular behavior, exceptions") {
    graph::Queue q(3);  // Queue of size 3

    CHECK(q.isEmpty() == true);

    SUBCASE("Enqueue within capacity") {
        CHECK_NOTHROW(q.enqueue(10));
        CHECK_NOTHROW(q.enqueue(20));
        CHECK_NOTHROW(q.enqueue(30));
        CHECK(q.isEmpty() == false);
    }

    SUBCASE("Enqueue beyond capacity should throw") {
        q.enqueue(1);
        q.enqueue(2);
        q.enqueue(3);
        CHECK_THROWS(q.enqueue(4));  // Should throw on overflow
    }

    SUBCASE("Dequeue should return correct values in FIFO order") {
        q.enqueue(5);
        q.enqueue(6);
        CHECK(q.dequeue() == 5);
        CHECK(q.dequeue() == 6);
    }

    SUBCASE("Dequeue from empty queue should throw") {
        CHECK_THROWS(q.dequeue());  // Should throw on underflow
    }

    SUBCASE("Circular enqueue after dequeue") {
        q.enqueue(100);
        q.enqueue(200);
        q.enqueue(300);
        CHECK(q.dequeue() == 100);
        CHECK_NOTHROW(q.enqueue(400)); // Should be allowed (circular logic)
        CHECK(q.dequeue() == 200);
        CHECK(q.dequeue() == 300);
        CHECK(q.dequeue() == 400);
        CHECK(q.isEmpty() == true);
    }

    SUBCASE("Queue full then empty completely") {
        q.enqueue(1);
        q.enqueue(2);
        q.enqueue(3);
        CHECK_THROWS(q.enqueue(4)); // Overflow

        CHECK(q.dequeue() == 1);
        CHECK(q.dequeue() == 2);
        CHECK(q.dequeue() == 3);
        CHECK(q.isEmpty() == true);

        CHECK_THROWS(q.dequeue()); // Underflow again
    }
}

// ============================
//         UNION-FIND SECTION
// ============================   

TEST_CASE("UNION-FIND - basic operations, structure integrity, path compression") {
    graph::UnionFind uf(6); // Create disjoint sets with 6 elements

    SUBCASE("Initial state - each node is its own parent") {
        for (int i = 0; i < 6; ++i) {
            CHECK(uf.find(i) == i); // Each element should be its own root
        }
    }

    SUBCASE("Unite two disjoint sets") {
        CHECK_NOTHROW(uf.unite(0, 1));
        CHECK(uf.find(0) == uf.find(1)); // 0 and 1 should have the same root
    }

    SUBCASE("Multiple unions - three sets into one") {
        uf.unite(0, 1);
        uf.unite(2, 3);
        uf.unite(1, 2); // Now all {0,1,2,3} should be in one set

        int root = uf.find(0);
        for (int i = 1; i <= 3; ++i) {
            CHECK(uf.find(i) == root);
        }
    }

    SUBCASE("Repeated unite calls on same pair") {
        uf.unite(0, 1);
        uf.unite(0, 1);
        uf.unite(1, 0);
        CHECK(uf.find(0) == uf.find(1)); // Should not cause problems
    }

    SUBCASE("Different sets remain disconnected") {
        uf.unite(0, 1);
        uf.unite(2, 3);
        CHECK(uf.find(0) != uf.find(2)); // {0,1} and {2,3} are separate
    }

    SUBCASE("Reset returns all elements to own set") {
        uf.unite(0, 1);
        uf.unite(2, 3);
        uf.reset();

        for (int i = 0; i < 6; ++i) {
            CHECK(uf.find(i) == i); // All sets should be singleton again
        }
    }

    SUBCASE("Self-union should not break structure") {
        uf.unite(4, 4);
        CHECK(uf.find(4) == 4);
    }

    
}
// ============================
//         EDGE SECTION
// ============================   

TEST_CASE("EDGE - construction, field access, copying") {

    SUBCASE("Create edge and access fields") {
        Edge e = {0, 1, 5};

        // Check field values
        CHECK(e.src == 0);
        CHECK(e.dst == 1);
        CHECK(e.weight == 5);
    }

    SUBCASE("Modify edge fields") {
        Edge e = {3, 4, 10};
        e.src = 1;
        e.dst = 2;
        e.weight = 7;

        CHECK(e.src == 1);
        CHECK(e.dst == 2);
        CHECK(e.weight == 7);
    }

    SUBCASE("Copy edge to another instance") {
        Edge e1 = {1, 2, 9};
        Edge e2 = e1;

        CHECK(e2.src == 1);
        CHECK(e2.dst == 2);
        CHECK(e2.weight == 9);

        // Modify one and ensure the other doesn't change
        e2.weight = 20;
        CHECK(e1.weight == 9);
        CHECK(e2.weight == 20);
    }

    SUBCASE("Use edge array") {
        Edge edges[2] = {{0, 1, 3}, {1, 2, 6}};

        CHECK(edges[0].src == 0);
        CHECK(edges[0].dst == 1);
        CHECK(edges[0].weight == 3);

        CHECK(edges[1].src == 1);
        CHECK(edges[1].dst == 2);
        CHECK(edges[1].weight == 6);
    }
}
// ============================
//         STACK SECTION
// ============================   

TEST_CASE("STACK - push, pop, peek, overflow, underflow") {
    graph::Stack s(3);  // Stack of capacity 3

    SUBCASE("Initially stack should be empty") {
        CHECK(s.isEmpty() == true);
    }

    SUBCASE("Push elements within capacity") {
        CHECK_NOTHROW(s.push(10));
        CHECK_NOTHROW(s.push(20));
        CHECK_NOTHROW(s.push(30));
        CHECK(s.isEmpty() == false);
    }

    SUBCASE("Push beyond capacity should throw") {
        s.push(1);
        s.push(2);
        s.push(3);
        CHECK_THROWS(s.push(4));  // Should throw overflow
    }

    SUBCASE("Pop returns elements in LIFO order") {
        s.push(5);
        s.push(6);
        s.push(7);

        CHECK(s.pop() == 7);
        CHECK(s.pop() == 6);
        CHECK(s.pop() == 5);
        CHECK(s.isEmpty() == true);
    }

    SUBCASE("Pop from empty stack should throw") {
        CHECK_THROWS(s.pop());  // Underflow
    }

    SUBCASE("Peek returns top element without removing") {
        s.push(100);
        s.push(200);

        CHECK(s.peek() == 200);   // Top is 200
        CHECK(s.peek() == 200);   // Still 200
        CHECK(s.pop() == 200);
        CHECK(s.peek() == 100);   // Now top is 100
    }

    SUBCASE("Self consistency with push/pop/peek") {
        CHECK(s.isEmpty() == true);
        s.push(42);
        CHECK(s.peek() == 42);
        CHECK(s.pop() == 42);
        CHECK(s.isEmpty() == true);
        CHECK_THROWS(s.peek());  // Stack is empty
    }
}

// ============================
//    PRIORITY-QUEUE SECTION
// ============================ 

TEST_CASE("PriorityQueue basic behavior") {
    PriorityQueue pq(3); // create a queue with capacity 3

    SUBCASE("check isEmpty on new queue") {
        CHECK(pq.isEmpty());
    }

    SUBCASE("insert and extractMin") {
        pq.insert(10, 5);
        CHECK_FALSE(pq.isEmpty());
        CHECK(pq.extractMin() == 10);
        CHECK(pq.isEmpty());
    }

    SUBCASE("extractMin returns vertex with lowest priority") {
        pq.insert(1, 30);
        pq.insert(2, 20);
        pq.insert(3, 10);
        CHECK(pq.extractMin() == 3); // has priority 10
        CHECK(pq.extractMin() == 2); // has priority 20
        CHECK(pq.extractMin() == 1); // has priority 30
    }

    SUBCASE("decreaseKey should update priority") {
        pq.insert(4, 40);
        pq.insert(5, 50);
        pq.decreaseKey(5, 5); // change priority of 5
        CHECK(pq.extractMin() == 5); // now 5 should come first
        CHECK(pq.extractMin() == 4);
    }

    SUBCASE("decreaseKey to higher value should do nothing") {
        pq.insert(6, 15);
        pq.decreaseKey(6, 100); // should not change
        CHECK(pq.extractMin() == 6);
    }

    SUBCASE("decreaseKey on non-existent vertex") {
        pq.decreaseKey(99, 1); // should not crash
        CHECK(pq.isEmpty());
    }

    SUBCASE("insert more than capacity") {
        pq.insert(1, 10);
        pq.insert(2, 20);
        pq.insert(3, 30);
        pq.insert(4, 5); // should not be added (overflow)
        CHECK(pq.extractMin() == 1);
        CHECK(pq.extractMin() == 2);
        CHECK(pq.extractMin() == 3);
        CHECK(pq.extractMin() == 2147483647); // queue is empty
    }

    SUBCASE("extractMin on empty queue") {
        CHECK(pq.extractMin() == 2147483647); // should return INT_MAX
    }
}

// ============================
//    ALGORITHMS SECTION - BFS
// ============================ 

TEST_CASE("BFS") {

    SUBCASE("bfs on connected graph") {
        Graph g(5);
        g.addEdge(0, 1, 1);
        g.addEdge(0, 2, 1);
        g.addEdge(1, 3, 1);
        g.addEdge(2, 4, 1);

        Graph bfsTree = Algorithms::bfs(g, 0);
        Node** adj = bfsTree.getAdjList();

        CHECK(adj[0] != nullptr);
        CHECK((adj[0]->vertex == 1 || adj[0]->vertex == 2));
        CHECK((adj[0]->next->vertex == 1 || adj[0]->next->vertex == 2));
        CHECK(adj[0]->vertex != adj[0]->next->vertex);

        CHECK(adj[1] != nullptr);
        CHECK(adj[1]->vertex == 3);

        CHECK(adj[2] != nullptr);
        CHECK(adj[2]->vertex == 4);

        CHECK(adj[3] == nullptr);
        CHECK(adj[4] == nullptr);
    }

    SUBCASE("bfs on graph with two components") {
        Graph g(6);
        g.addEdge(0, 1, 1);
        g.addEdge(1, 2, 1);
        g.addEdge(3, 4, 1); // disconnected component

        Graph bfsTree = Algorithms::bfs(g, 0);
        Node** adj = bfsTree.getAdjList();

        CHECK(adj[0] != nullptr);
        CHECK(adj[1] != nullptr);
        CHECK(adj[2] == nullptr);

        CHECK(adj[3] == nullptr);
        CHECK(adj[4] == nullptr);
        CHECK(adj[5] == nullptr);
    }

    SUBCASE("bfs with invalid start node") {
        Graph g(4);
        g.addEdge(0, 1, 1);
        g.addEdge(1, 2, 1);

        CHECK_THROWS_AS(Algorithms::bfs(g, -1), std::out_of_range);
        CHECK_THROWS_AS(Algorithms::bfs(g, 4), std::out_of_range);
        CHECK_THROWS_AS(Algorithms::bfs(g, 99), std::out_of_range);
    }

    SUBCASE("bfs on single-node graph") {
        Graph g(1);
        Graph bfsTree = Algorithms::bfs(g, 0);
        CHECK(bfsTree.getAdjList()[0] == nullptr);
    }
}

// ============================
//    ALGORITHMS SECTION - DFS
// ============================ 

TEST_CASE("DFS") {

    SUBCASE("dfs on connected graph") {
        Graph g(5);
        g.addEdge(0, 1, 1);
        g.addEdge(1, 2, 1);
        g.addEdge(2, 3, 1);
        g.addEdge(3, 4, 1);

        Graph dfsTree = Algorithms::dfs(g, 0);
        Node** adj = dfsTree.getAdjList();

        // check tree structure (0 -> 1 -> 2 -> 3 -> 4)
        CHECK(adj[0] != nullptr);
        CHECK(adj[0]->vertex == 1);
        CHECK(adj[1] != nullptr);
        CHECK(adj[1]->vertex == 2);
        CHECK(adj[2] != nullptr);
        CHECK(adj[2]->vertex == 3);
        CHECK(adj[3] != nullptr);
        CHECK(adj[3]->vertex == 4);
        CHECK(adj[4] == nullptr); // leaf
    }

    SUBCASE("dfs on graph with two components") {
        Graph g(6);
        g.addEdge(0, 1, 1);
        g.addEdge(1, 2, 1);
        g.addEdge(3, 4, 1); // disconnected component

        Graph dfsTree = Algorithms::dfs(g, 0);
        Node** adj = dfsTree.getAdjList();

        // only 0,1,2 reachable
        CHECK(adj[0] != nullptr);
        CHECK(adj[1] != nullptr);
        CHECK(adj[2] == nullptr); // leaf

        // others not reachable
        CHECK(adj[3] == nullptr);
        CHECK(adj[4] == nullptr);
        CHECK(adj[5] == nullptr);
    }

    SUBCASE("dfs with invalid start index") {
        Graph g(4);
        g.addEdge(0, 1, 1);
        g.addEdge(1, 2, 1);

        CHECK_THROWS_AS(Algorithms::dfs(g, -1), std::out_of_range);
        CHECK_THROWS_AS(Algorithms::dfs(g, 4), std::out_of_range);
    }

    SUBCASE("dfs on single-node graph") {
        Graph g(1);
        Graph dfsTree = Algorithms::dfs(g, 0);
        CHECK(dfsTree.getAdjList()[0] == nullptr);
    }
}

// ============================
// ALGORITHMS SECTION - DIJKSTRA
// ============================ 

TEST_CASE("dijkstra basic behavior") {

    SUBCASE("dijkstra on connected graph") {
        Graph g(5);
        g.addEdge(0, 1, 2);
        g.addEdge(1, 2, 4);
        g.addEdge(0, 3, 1);
        g.addEdge(3, 2, 1);
        g.addEdge(2, 4, 3);

        Graph shortestTree = Algorithms::dijkstra(g, 0);
        Node** adj = shortestTree.getAdjList();

        // expected path: 0 -> 3 -> 2 -> 4 and 0 -> 1
        CHECK(adj[0] != nullptr);
        CHECK((adj[0]->vertex == 1 || adj[0]->vertex == 3));
        CHECK((adj[0]->next->vertex == 1 || adj[0]->next->vertex == 3));
        CHECK(adj[0]->vertex != adj[0]->next->vertex);

        // 3 points to 2
        CHECK(adj[3] != nullptr);
        CHECK(adj[3]->vertex == 2);

        // 2 points to 4
        CHECK(adj[2] != nullptr);
        CHECK(adj[2]->vertex == 4);

        // 1 and 4 are leaves
        CHECK(adj[1] == nullptr);
        CHECK(adj[4] == nullptr);
    }

    SUBCASE("dijkstra on graph with two components") {
        Graph g(6);
        g.addEdge(0, 1, 1);
        g.addEdge(1, 2, 1);
        g.addEdge(3, 4, 1); // second component

        Graph shortestTree = Algorithms::dijkstra(g, 0);
        Node** adj = shortestTree.getAdjList();

        // only 0,1,2 reachable
        CHECK(adj[0] != nullptr);
        CHECK(adj[1] != nullptr);
        CHECK(adj[2] == nullptr);

        // others not reachable
        CHECK(adj[3] == nullptr);
        CHECK(adj[4] == nullptr);
        CHECK(adj[5] == nullptr);
    }

    SUBCASE("dijkstra with invalid start index") {
        Graph g(4);
        g.addEdge(0, 1, 1);
        g.addEdge(1, 2, 1);

        CHECK_THROWS_AS(Algorithms::dijkstra(g, -1), std::out_of_range);
        CHECK_THROWS_AS(Algorithms::dijkstra(g, 4), std::out_of_range);
    }

    SUBCASE("dijkstra on single-node graph") {
        Graph g(1);
        Graph shortestTree = Algorithms::dijkstra(g, 0);
        CHECK(shortestTree.getAdjList()[0] == nullptr);
    }
}

// ============================
// ALGORITHMS SECTION - PRIM
// ============================ 

TEST_CASE("PRIM") {

    SUBCASE("prim on connected graph") {
        Graph g(5);
        g.addEdge(0, 1, 2);
        g.addEdge(0, 3, 6);
        g.addEdge(1, 2, 3);
        g.addEdge(1, 3, 8);
        g.addEdge(1, 4, 5);
        g.addEdge(2, 4, 7);
        g.addEdge(3, 4, 9);

        Graph mst = Algorithms::prim(g);
        Node** adj = mst.getAdjList();

        // The MST should have exactly 4 edges (undirected → appears 8 times)
        int edgeCount = 0;
        for (int i = 0; i < 5; ++i) {
            Node* curr = adj[i];
            while (curr != nullptr) {
                edgeCount++;
                curr = curr->next;
            }
        }

        CHECK(edgeCount == 8); // 4 edges × 2 sides
    }

    SUBCASE("prim on graph with two components") {
        Graph g(6);
        g.addEdge(0, 1, 1);
        g.addEdge(1, 2, 2);
        g.addEdge(3, 4, 3); // disconnected component

        Graph mst = Algorithms::prim(g);
        Node** adj = mst.getAdjList();

        // only the component 0-1-2 should appear
        CHECK(adj[0] != nullptr);
        CHECK(adj[1] != nullptr);
        CHECK(adj[2] != nullptr);

        // component 3-4 should not be touched
        CHECK(adj[3] == nullptr);
        CHECK(adj[4] == nullptr);
        CHECK(adj[5] == nullptr);
    }

    SUBCASE("prim on single node") {
        Graph g(1);
        Graph mst = Algorithms::prim(g);
        CHECK(mst.getAdjList()[0] == nullptr);
    }
}

// ============================
// ALGORITHMS SECTION - KRUSKAL
// ============================ 

TEST_CASE("KRUSKAL") {

    SUBCASE("kruskal on connected graph") {
        Graph g(5);
        g.addEdge(0, 1, 1);
        g.addEdge(0, 2, 5);
        g.addEdge(1, 2, 3);
        g.addEdge(1, 3, 4);
        g.addEdge(2, 4, 2);

        Graph mst = Algorithms::kruskal(g);
        Node** adj = mst.getAdjList();

        // The MST should have exactly 4 edges => 8 nodes in undirected adj list
        int edgeCount = 0;
        for (int i = 0; i < 5; ++i) {
            Node* curr = adj[i];
            while (curr != nullptr) {
                edgeCount++;
                curr = curr->next;
            }
        }

        CHECK(edgeCount == 8); // undirected: each edge appears twice
    }

    SUBCASE("kruskal on graph with two components") {
        Graph g(6);
        g.addEdge(0, 1, 1);
        g.addEdge(1, 2, 2);
        g.addEdge(3, 4, 3); // disconnected component

        Graph mst = Algorithms::kruskal(g);
        Node** adj = mst.getAdjList();

        // component 0-1-2
        CHECK(adj[0] != nullptr);
        CHECK(adj[1] != nullptr);
        CHECK(adj[2] != nullptr);

        // component 3-4 (only one edge, should be included too)
        CHECK(adj[3] != nullptr);
        CHECK(adj[4] != nullptr);

        // node 5 is isolated
        CHECK(adj[5] == nullptr);
    }

    SUBCASE("kruskal on graph with no edges") {
        Graph g(3);
        Graph mst = Algorithms::kruskal(g);
        Node** adj = mst.getAdjList();

        CHECK(adj[0] == nullptr);
        CHECK(adj[1] == nullptr);
        CHECK(adj[2] == nullptr);
    }

    SUBCASE("kruskal on single node") {
        Graph g(1);
        Graph mst = Algorithms::kruskal(g);
        CHECK(mst.getAdjList()[0] == nullptr);
    }
}
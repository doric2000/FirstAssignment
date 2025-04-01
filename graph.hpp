// dor.cohen15@msmail.ariel.ac.il


#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <stdexcept>

using namespace std;

namespace graph {

    int find(int* parent, int i);
    void unionSets(int* parent, int* rank, int x, int y);


    struct Node { //stands for a Neighbor of a vertex.
        int vertex; // number of the vertex
        int weight;
        Node* next; // a pointer to the next one.
    
        Node(int v,int w) : vertex(v) ,weight(w) , next(nullptr){}    // initialization list
    };

    class Queue { // it will help us implement the bfs / dfs
        int* data; // an array of the indexes ?
        int front,rear,size,capacity; // first, last , current size , capacity
        public:
            bool enqueue(int vertex); // add a vertex to the stack.
            int dequeue(); // remove the first vertex of the stack.
            bool isEmpty(); // check if the stack is empty
            Queue(int capacity);                 // constructor (does the size is necesiry?)
            ~Queue();                                //  desctructor


    };

    struct Edge {
        int src, dst, weight;
    };

    class Stack {
        int* data;
        int top;
        int capacity;
        int size;

        public:
        void push(int vertex);
        int pop();
        int peek();
        bool isEmpty();
        Stack(int capacity);                 // constructor (does the size is necesiry?)
        ~Stack();                                //  desctructor

    };

    struct HeapNode {
        int vertex;    // num of vertexes
        int priority;  // current distance from source.
    };

    class PriorityQueue {
        
        private:
            HeapNode* heap;    // array of vertexes
            int size;          // current vertexes in our queue
            int capacity;      // ... capacity..
            void heapifyUp(int index);
            void heapifyDown(int index);

        public:
            void insert(int value, int priority);
            int extractMin();
            void decreaseKey(int value, int newPriority);
            bool isEmpty();
            PriorityQueue(int capacity);
            ~PriorityQueue();
    };



    class Graph{
  
        private:
            int numVertices; // const number of Vertices of the Graph
            Node** adjList; // will be treated as array that in each cell has a list of nodes.
        
        public:
            Node** getAdjList();
            int getNumVertices();
            Graph(int vertices);                      // constructor
            ~Graph();                                //  desctructor
        

        public:
            /**
             * @brief add an edge in the graph between src and dst
             * 
             * @param src edge from
             * @param dst to
             * @param weight default weight will be 1
             */
            void addEdge(int src,int dst,int weight);

            /**
             * @brief removing an edge in the graph between src and dst
             * 
             * @param src edge from
             * @param dst to
             */
            void removeEdge(int src , int dst); //removing an edge from the graph

            /**
             * @brief printing the graph in some way that i havent discover yet.
             * 
             */
            void print_graph(); // print the graph in a logical way
            
                        
            /**
             * @brief Adds a one-way edge from src to dst.
             * 
             * Creates a directed edge with the given weight (default is 1).
             * Does not add the reverse edge.
             * 
             * @param src Source vertex.
             * @param dst Destination vertex.
             * @param weight Edge weight.
             */
            void addDirectedEdge(int src, int dst, int weight = 1);
        };

    class Algorithms{
    public:

    static Graph bfs(Graph& g , int start);
    static Graph dfs(Graph& g, int start);
    static Graph dijkstra(Graph& g, int start);
    static Graph prim(Graph& g);
    static Graph kruskal(Graph& g);
    static void relax(int u, int v, int weight, int* distances, int* parent, PriorityQueue& pq);       

    };

};

 // namespace graph

#endif // GRAPH_HPP
#include "graph.hpp"
using namespace graph;

namespace graph{
    
// ============================
//         STACK SECTION
// ============================

    Stack::Stack(int capacity) 
    {
        this->capacity = capacity;
        this->data = new int[capacity];
        this->top = -1;
        this->size = 0;
    }
    
    Stack::~Stack(){
        delete[] data;
    }

    /**
     * @brief Pushes a vertex onto the top of the stack.
     * 
     * This function inserts the given vertex at the top of the stack,
     * if the stack is not already full.
     * 
     * @param vertex The vertex to be pushed onto the stack.
     */
    void Stack::push(int vertex) {
        if (this->top >= this->capacity - 1) {
            std::cout << "Stack is full" << std::endl;
            return;
        }
        this->data[++top] = vertex;
        size++;
    }

    /**
     * @brief Removes and returns the top element of the stack.
     * 
     * This function pops the top value from the stack and returns it.
     * If the stack is empty, it returns 2147483647 as an error value.
     * 
     * @return int The value that was on top of the stack, or 2147483647 if the stack is empty.
     */
    int Stack::pop() {
        if (top != -1) {
            size--;
            return this->data[top--];
        } else {
            return 2147483647; 
        }
    }
    
    /**
     * @brief Checks whether the stack is empty.
     * 
     * This function returns a boolean value indicating whether the stack
     * currently contains any elements. It checks if the 'size' variable is 0,
     * which implies that the stack is empty.
     * 
     * @return true If the stack is empty.
     * @return false If the stack contains one or more elements.
     */
    bool Stack::isEmpty(){
        if (this->size == 0)
            return true;
        return false;
    }

    /**
     * @brief Returns the top element of the stack without removing it.
     * 
     * This function retrieves the value at the top of the stack without modifying the stack.
     * If the stack is empty, it returns 2147483647 as an error value.
     * 
     * @return int The value at the top of the stack, or 2147483647 if the stack is empty.
     */
    int Stack::peek() {
        if (top != -1) {
            return this->data[top];
        } else {
            return 2147483647;  // or consider throwing an exception
        }
    }
    
    
     
    
 // ============================
//         QUEUE SECTION
// ============================   
    
    Queue::Queue(int capacity) 
    {
        this->capacity = capacity;
        this->data = new int[capacity];
        this->front = 0;
        this->rear = 0;
        this->size = 0;
    }
    Queue::~Queue(){
        delete[] data;
    }

    /**
     * @brief Adds a vertex to the end of the queue.
     * 
     * This function inserts the given vertex into the queue,
     * if the queue is not already full.
     * 
     * @param vertex The vertex to be enqueued.
     * @return true If the vertex was successfully enqueued.
     * @return false If the queue is full and the vertex could not be enqueued.
     */
    bool Queue::enqueue(int vertex) {
        if (size < capacity) {
            this->data[rear] = vertex;
            this->rear = (this->rear + 1) % this->capacity;
            this->size++;
            return true;
        } else {
            return false;
        }
    }

    /**
     * @brief Removes and returns the front element from the queue.
     * 
     * This function dequeues the element at the front of the queue.
     * If the queue is empty, it returns a special value (INT_MAX).
     * 
     * @return int The value at the front of the queue. If the queue is empty, returns 2147483647 (INT_MAX).
     */
    int Queue::dequeue() {
        if (isEmpty()) {
            return 2147483647;  // Or consider throwing an exception instead
        }
        int firstVer = this->data[front];
        this->front = (this->front + 1) % this->capacity;
        this->size--;
        return firstVer;
    }

    /**
     * @brief Checks if the queue is empty.
     * 
     * This function returns true if there are no elements in the queue,
     * i.e., the current size is zero.
     * 
     * @return true if the queue is empty.
     * @return false if the queue contains one or more elements.
     */
    bool Queue::isEmpty()
    {
        return this->size == 0;
    }

// ============================
//     PRIORITY QUEUE SECTION
// ============================
    
PriorityQueue::PriorityQueue(int capacity) {
    this->capacity = capacity;
    this->heap = new HeapNode[capacity];
    this->size = 0;
}

PriorityQueue::~PriorityQueue() {
    delete[] heap;
}

void PriorityQueue::insert(int vertex, int priority) {
    if (size == capacity) {
        std::cout << "Priority Queue is full." << std::endl;
        return;
    }
    heap[size] = {vertex, priority};
    heapifyUp(size);
    size++;
}

int PriorityQueue::extractMin() {
    if (isEmpty()) {
        std::cout << "Priority Queue is empty." << std::endl;
        return 2147483647;
    }
    int minVertex = heap[0].vertex;
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0);
    return minVertex;
}

void PriorityQueue::decreaseKey(int vertex, int newPriority) {
    for (int i = 0; i < size; i++) {
        if (heap[i].vertex == vertex) {
            if (newPriority < heap[i].priority) {
                heap[i].priority = newPriority;
                heapifyUp(i);
            }
            break;
        }
    }
}

bool PriorityQueue::isEmpty() {
    return size == 0;
}

void PriorityQueue::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent].priority <= heap[index].priority) {
            break;
        }
        std::swap(heap[parent], heap[index]);
        index = parent;
    }
}

void PriorityQueue::heapifyDown(int index) {
    while (2 * index + 1 < size) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && heap[left].priority < heap[smallest].priority) {
            smallest = left;
        }
        if (right < size && heap[right].priority < heap[smallest].priority) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }
        std::swap(heap[index], heap[smallest]);
        index = smallest;
    }
}

// ============================
//         UNION SET SECTION
// ============================  

int find(int* parent, int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

void unionSets(int* parent, int* rank, int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}


    
// ============================
//         GRAPH SECTION
// ============================  


    Graph::Graph(int vertices)
    {
        this->numVertices = vertices;
        this->adjList = new Node* [vertices];
        for (int i = 0; i < vertices; ++i) {
            adjList[i] = nullptr;
        }
    }

    Graph::~Graph(){
        for (int i = 0; i < numVertices; i++)
        {
            Node* current = adjList[i];
            while (current != nullptr)
            {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] adjList;

    }

    int Graph::getNumVertices(){
        return this->numVertices;

    }

    Node** Graph::getAdjList(){
        return adjList;
    }

    void Graph::addEdge(int src,int dst,int weight=1) 
    {
        Node* edge1 = new Node(dst,weight);
        edge1->next = adjList[src];
        adjList[src] = edge1; 

        Node* edge2 = new Node(src,weight);
        edge2->next = adjList[dst];
        adjList[dst] = edge2;
    }

    void Graph::removeEdge(int src,int dst) 
    {
        // first side delete:
        Node* curr = adjList[src];  
        Node* prev = nullptr;
        
        while (curr!= nullptr && curr->vertex != dst) // while there are vertexes and the current vertex is not the one we are looking for.
        {
            prev = curr;
            curr = curr->next;
        }

        if (curr!= nullptr){
            if (prev == nullptr) { //if curr is the head than delete the head
                
                adjList[src] = curr->next;
            }
            else{               // if curr is between two nodes than skip curr.
                prev->next = curr->next;
            }

            delete curr; // now we will have to clean the mem
        }


        // second side delete:
        curr = adjList[dst]; 
        prev = nullptr;

        while (curr!= nullptr && curr->vertex != src) // while there are vertexes and the current vertex is not the one we are looking for.
        {
            prev = curr;
            curr = curr->next;
        }

        if (curr!= nullptr){
            if (prev == nullptr) { //if curr is the head than delete the head
                
                adjList[dst] = curr->next;
            }
            else{               // if curr is between two nodes than skip curr.
                prev->next = curr->next;
            }

            delete curr; // now we will have to clean the mem
        }

    }

    void Graph::addDirectedEdge(int src, int dst, int weight) {
        Node* edge = new Node(dst, weight);
        edge->next = adjList[src];
        adjList[src] = edge;
    }

    void Graph::print_graph()
    {
        std::cout << "Graph adjacency list: \n";
        for (int i = 0; i < this->numVertices; i++)
        {
            std::cout << i << " ---> ";
            Node* temp = adjList[i];
            while (temp != nullptr){
                std::cout << "(" << temp->vertex << ", weight = " << temp->weight << ") ";
                temp = temp->next;
            }
            std::cout << std::endl;
        }
        
    }


} // namespace graph
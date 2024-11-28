#include <iostream>
#include <vector>
#include <algorithm>    
using namespace std;

const unsigned int UNREACHABLE = -1;

// Node struct represents an edge connecting to another vertex in the graph.
struct Node {
    int toKey;
    int distance;
    Node *next;
};

// Vertex struct represents each vertex in the graph.
struct Vertex {
    int key;                                        // unique identifier for the vertex                
    Node *adjacents = nullptr;                      // initialised as null since it is not connected to any other vertex yet.
    char state = 't';                               // state initialised as t (unvisited)
    unsigned int minDistance = UNREACHABLE;         // initialised as unreachable (infinity)
};

// Struct to compare two vertices, control how elements are ordered, and maintain a min-heap.
struct VertexComparison {
    bool operator()(Vertex*& vertex1, Vertex*& vertex2) {
        return vertex1->minDistance > vertex2->minDistance;     // greater operator to maintain a min-heap property
    }
};

vector<Vertex*> vertices;

void addVertex(int key);
void addEdge(int fromKey, int toKey, int distance);
void addEdgeToFront(Node*& adjacents, int toKey, int distance);
void findShortestPathDijkstraAlgorithm();
void printMinimumDistances();

// Function to add vertex to the vector
void addVertex(int key){
    Vertex *temp = new Vertex;
    temp->key = key;
    temp->adjacents = NULL;

    vertices.push_back(temp);
}

// Function to add egde to a vertex
void addEdge(int fromKey, int toKey, int distance){
    for (int i = 0; i < (int)vertices.size(); i++){
        if (fromKey == vertices[i]->key){
            addEdgeToFront(vertices[i]->adjacents, toKey, distance);            // call addEdgeToFront method and pass the current vertex's adjacents
        }
    }
}

// Function to create a graph by connecting the vertex/nodes and edges for a graph
void addEdgeToFront(Node*& currentVertexAdjacents, int toKey, int distance){
    Node *temp = new Node;
    temp->toKey = toKey;

    if (distance >= 1 && distance <= 99){           // Make sure the distance is between 1 to 99
        temp->distance = distance;
    } else {
        throw out_of_range("Distance must be between 1 to 99.");
    }
    temp->next = currentVertexAdjacents;
    currentVertexAdjacents = temp;
}

// Function to find the shortest path using Dijkstra's algorithm
void findShortestPathDijkstraAlgorithm(){

    vector<Vertex*> heap;

    Vertex *sourceVertex = vertices[0];                                     // source vertex which located at the vertices vector element 0
    sourceVertex->minDistance = 0;                                          // set the source vertex minimum distance to 0 since it is the source vertex
    heap.push_back(sourceVertex);                                           // push the source vertex into the heap
    push_heap(heap.begin(), heap.end(), VertexComparison());                // vertex with the shortest distance will be at the top of the heap (min-heap)

    while (heap.empty() == false){
        pop_heap(heap.begin(), heap.end(), VertexComparison());             // move element with the smallest minimum distance to the end
        Vertex *currentNode = heap.back();                              
        heap.pop_back();

        if (currentNode->state == 'p'){                                     // Check if the current vertex is permanent, if it is, skip it. Otherwise, set it to permanent.
            continue;
        } 
        currentNode->state = 'p';
        
        Node *temp = currentNode->adjacents;                                // get the adjacents of the current vertex

        while (temp != nullptr){                                            // Since adjacents can be more than 1, make sure to process all of them
            int adjacentKey = temp->toKey;
            int adjacentDistance = temp->distance;

            Vertex *currentAdjacent = vertices[adjacentKey];
            
            /**
             * Distance to an adjacent vertex is calculated as:
             * current vertex's minimum distance + edge weight to the adjacent vertex
             * if this calculated distance is smaller than the adjacent vertex's current minimum distance,
             * the adjacent vertex's minimum distance is updated.
             * 
             * Example: For edge (vertex 0 -> vertex 1) with weight 4.
             * distance to adjacent = 0 (min distance of vertex 0) + 4 (edge weight) = 4
             * since vertex 1's current minimum distance is infinity, it is updated to 4.
             */
            unsigned int distanceToAdjacent = currentNode->minDistance + adjacentDistance;
            
            if (distanceToAdjacent < currentAdjacent->minDistance){         
                currentAdjacent->minDistance = distanceToAdjacent;
                heap.push_back(currentAdjacent);
                push_heap(heap.begin(), heap.end(), VertexComparison());    // keep maintaining the min-heap property since new element is added
            }
            temp = temp->next;                                              // move to the next adjacent if available                                 
        } 
    }
}


// Function to print distances from source vertex to all the vertices in the graph
void printMinimumDistances(){
    for (int i = 0; i < (int)vertices.size(); i++){
        unsigned int currentVertexMinDistance = vertices[i]->minDistance;
        if (currentVertexMinDistance == UNREACHABLE){                       // if unreachable, print infinity 
            cout << "Infinity ";
        } else {
            cout << currentVertexMinDistance << " ";
        }
    }
}

int main(){
    int totalVertices, totalEdges, fromVertex, toVertex, distance;

    cin >> totalVertices >> totalEdges;

    for (int i = 0; i < totalVertices; i++){
        addVertex(i);
    }

    for (int i = 0; i < totalEdges; i++){
        cin >> fromVertex >> toVertex >> distance;
        addEdge(fromVertex, toVertex, distance);
    }

    findShortestPathDijkstraAlgorithm();
    printMinimumDistances();

    return 0;
}
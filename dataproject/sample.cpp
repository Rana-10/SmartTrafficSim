#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    char vertx; // Vertex label
    int weight; // Edge weight
    Node *next; // Pointer to the next node

    Node(char ver, int w)
    {
        vertx = ver;
        weight = w;
        next = nullptr;
    }
};

class Graph
{
public:
    Node **array;  // Array of linked lists for adjacency representation
    int num_nodes; // Total number of nodes in the graph

    // Constructor
    Graph(int size)
    {
        num_nodes = size;
        array = new Node *[num_nodes];
        for (int i = 0; i < num_nodes; ++i)
        {
            array[i] = nullptr;
        }
    }

    // Add undirected edge
    void addEdge(char src, char dest, int weight)
    {
        int indexSrc = src - 'A'; // Convert character to index
        int indexDest = dest - 'A';

        // Add edge from src to dest
        Node *newNodeSrc = new Node(dest, weight);
        newNodeSrc->next = array[indexSrc];
        array[indexSrc] = newNodeSrc;

        // Add edge from dest to src (for undirected graph)
        Node *newNodeDest = new Node(src, weight);
        newNodeDest->next = array[indexDest];
        array[indexDest] = newNodeDest;
    }

    // Print the graph
    void printGraph()
    {
        for (int i = 0; i < num_nodes; ++i)
        {
            cout << char('A' + i) << " -> ";
            Node *temp = array[i];
            while (temp)
            {
                cout << "(" << temp->vertx << ", " << temp->weight << ") ";
                temp = temp->next;
            }
            cout << endl;
        }
    }

    // Destructor to free memory
    ~Graph()
    {
        for (int i = 0; i < num_nodes; ++i)
        {
            Node *temp = array[i];
            while (temp)
            {
                Node *toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }
        }
        delete[] array;
    }
};

int main()
{
    int numNodes = 6; // A, B, C, D, E, F
    Graph g(numNodes);

    // Adding undirected edges
    g.addEdge('A', 'B', 40);
    g.addEdge('A', 'C', 20);
    g.addEdge('B', 'D', 50);
    g.addEdge('C', 'D', 30);
    g.addEdge('D', 'E', 10);
    g.addEdge('E', 'F', 60);

    // Print the graph
    g.printGraph();

    return 0;
}

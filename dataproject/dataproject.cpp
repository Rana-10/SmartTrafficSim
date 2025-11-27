// Data Structures Project Fall 2024
// Abdullah Ilyas 23i-2603
// Mahd Kazmi 23i-2587
// Muhammad Azmat 23i-2651

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Node
{
public:
    char vertx;
    int weight;
    string status;
    Node *next;

    Node(char ver, int w, string st = "Clear")
    {
        vertx = ver;
        weight = w;
        next = nullptr;
    }
};
struct PathNode
{
    int path[26];
    int pathLen;
};
class Graph
{
public:
    Node **array;
    int num_nodes;

    Graph(int size)
    {
        num_nodes = size;
        array = new Node *[num_nodes];
        for (int i = 0; i < num_nodes; i++)
        {
            array[i] = nullptr;
        }
    }

    void addEdge(char point_1, char point_2, int weight, string st = "Clear")
    {

        int a = point_1 - 'A';
        int b = point_2 - 'A';
        Node *n_node_start = new Node(point_2, weight, st);
        // insert at tail
        if (array[a] == nullptr) // if list  is empty  insertion at head
        {
            array[a] = n_node_start;
        }
        else
        {
            Node *temp = array[a];
            while (temp->next != nullptr) // insertion at tail
            {
                temp = temp->next;
            }
            temp->next = n_node_start;
        }

        Node *n_node_end = new Node(point_1, weight, st);

        // insert at tail
        if (array[b] == nullptr)
        {
            array[b] = n_node_end;
        }
        else
        {
            Node *temp = array[b];
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = n_node_end;
        }
    }

    void dijkstra(char a, char b, int roadCounts[26][26])
    {
        // index to iterate list
        int A_point = a - 'A';
        int B_point = b - 'A';
        int *distance = new int[num_nodes];
        bool *visited = new bool[num_nodes];  // check which noode has been visited
        char *prevoius = new char[num_nodes]; // array to store prevoius node
        int *PQ = new int[num_nodes];         // priority queue
        int queue_size = 0;

        for (int i = 0; i < num_nodes; i++)
        {
            distance[i] = 10000000; // in dijsktra each node distance first marked as infinity so we take large number
            visited[i] = false;
            prevoius[i] = '\0';
            PQ[i] = -1;
        }
        distance[A_point] = 0;
        PQ[queue_size++] = A_point;

        while (queue_size > 0)
        {
            int min_index = -1;
            int value = 10000000;
            for (int i = 0; i < queue_size; i++)
            {
                int k = PQ[i];
                if (!visited[k] && distance[k] < value)
                {
                    value = distance[k];
                    min_index = k;
                }
            }

            if (min_index == -1)
                break;

            for (int i = 0; i < queue_size; i++)
            {
                if (PQ[i] == min_index)
                {
                    queue_size = queue_size - 1;
                    PQ[i] = PQ[queue_size];
                    break;
                }
            }

            visited[min_index] = true;

            Node *temp = array[min_index];
            while (temp)
            {
                int index = temp->vertx - 'A';

                if (temp->status == "Blocked") // skip if road is blocked
                {
                    temp = temp->next;
                    continue;
                }

                if (!visited[index] && distance[min_index] + temp->weight < distance[index])
                {
                    distance[index] = distance[min_index] + temp->weight;
                    prevoius[index] = min_index + 'A';

                    bool inQueue = false;
                    for (int i = 0; i < queue_size; i++)
                    {
                        if (PQ[i] == index)
                        {
                            inQueue = true;
                            break;
                        }
                    }
                    if (!inQueue)
                    {
                        PQ[queue_size++] = index;
                    }
                }
                temp = temp->next;
            }
        }

        char path[num_nodes];
        int l = 0; // lenght of path

        int i = B_point;
        while (i != '\0' - 'A')
        {
            path[l] = i + 'A';
            l++;
            i = prevoius[i] - 'A';
        }
        // reverse the path as it store in reverse oder so we revrese it and then print
        for (int i = 0; i < l / 2; i++)
        {
            char temp = path[i];
            path[i] = path[l - 1 - i];
            path[l - 1 - i] = temp;
        }
        // count the number of times each road is used and vehciles are counted on basis of path
        for (int i = 0; i < l - 1; i++)
        {
            char A_point = path[i];
            char B_point = path[i + 1];
            roadCounts[A_point - 'A'][B_point - 'A'] = roadCounts[A_point - 'A'][B_point - 'A'] + 1;
            roadCounts[B_point - 'A'][A_point - 'A'] = roadCounts[B_point - 'A'][A_point - 'A'] + 1;
        }

        // printing path
        cout << "Shortest path from " << a << " to " << b << ": ";
        for (int i = 0; i < l; i++)
        {
            cout << path[i] << " ";
        }
        cout << "with total distance: " << distance[B_point] << endl;

        delete[] distance;
        delete[] visited;
        delete[] prevoius;
        delete[] PQ;
    }

    void display_graph()
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

    string check_road_status(char start, char end)
    {
        int a = start - 'A';
        int b = end - 'A';

        Node *temp = array[a];
        while (temp)
        {
            if (temp->vertx == end)
            {
                return temp->status;
            }
            temp = temp->next;
        }

        return "No road between "; // No road exists between the two nodes
    }

    void displayblockroads()
    {
        for (int i = 0; i < num_nodes; i++)
        {
            Node *temp = array[i];
            while (temp)
            {
                if (temp->status == "Blocked")
                {

                    cout << char('A' + i) << " to " << temp->vertx << " is blocked" << endl;
                    break;
                }
                temp = temp->next;
            }
        }
    }

    void blocking_road(char start, char end)
    {
        if (check_road_status(start, end) == "Blocked")
        {
            cout << "Road is already blocked" << endl;
            return;
        }
        else if (check_road_status(end, start) == "No road between")
        {
            cout << "no road between " << start << " and " << end << endl;
            return;
        }
        Node *temp = array[start - 'A'];
        while (temp)
        {
            if (temp->vertx == end)
            {
                temp->status = "Blocked";
                break;
            }
            temp = temp->next;
        }

        temp = array[end - 'A'];
        while (temp)
        {
            if (temp->vertx == start)
            {
                temp->status = "Blocked";
                break;
            }
            temp = temp->next;
        }
    }
    int find_path_weight(string whole_path)
    {
        int l = whole_path.length();
        int total_weight = 0;
        for (int i = 0; i < l - 1; i++)
        {
            char A_point = whole_path[i];
            char B_point = whole_path[i + 1];
            // here we are finding the weight of the path first calculate 0 index and 1 index weight and incrementally adding the weight
            Node *temp = array[A_point - 'A'];
            while (temp && temp->vertx != B_point)
            {
                temp = temp->next;
            }
            if (temp)
            {
                total_weight = total_weight + temp->weight;
            }
        }
        return total_weight;
    }

    void print_all_path(char start, char end)
    {
        bool visited[26] = {false};
        char path[26];
        int length = 0;
        path_printing(start - 'A', end - 'A', visited, path, length);
    }

    void path_printing(int current, int dest, bool visited[], char path[], int path_length)
    {
        visited[current] = true;
        path[path_length] = current + 'A';

        if (current == dest)
        {
            string whole_path(path, path_length + 1);
            int totalWeight = find_path_weight(whole_path);
            cout << whole_path << " Total Weight: " << totalWeight << endl;
        }
        else
        {
            Node *temp = array[current];
            while (temp)
            {
                int next_point = temp->vertx - 'A';
                if (!visited[next_point] && temp->status != "Blocked")
                {
                    path_printing(next_point, dest, visited, path, path_length + 1);
                }
                temp = temp->next;
            }
        }

        visited[current] = false;
    }
};

class Vehicle
{
public:
    string ID;
    char Start;
    char End;

    Vehicle()
    {
        ID = "";
        Start = '\0';
        End = '\0';
    }

    void add_vehicle(string id, char start, char end)
    {
        ID = id;
        Start = start;
        End = end;
    }
    void display()
    {
        cout << "vehicle  " << ID << ", point  " << Start << " to " << End << endl;
    }
};

class Trafic_signal
{
public:
    char node;
    int green_duration;

    Trafic_signal()
    {
        node = '\0';
        green_duration = 0;
    }

    void add_signal(char n, int duration)
    {
        node = n;
        green_duration = duration;
    }

    void display()
    {
        cout << "Interaction " << node << ", Green Time: " << green_duration << "s" << endl;
    }
};
class EmergencyVehicle
{
public:
    string ID;
    char Start;
    char End;
    string PriorityLevel;

    EmergencyVehicle()
    {
        ID = "";
        Start = '\0';
        End = '\0';
        PriorityLevel = "";
    }

    void add_emergency_vehicle(string id, char start, char end, string priority)
    {
        ID = id;
        Start = start;
        End = end;
        PriorityLevel = priority;
    }
};

// read graph
void read_nodes(string filename, Graph &g)
{
    ifstream file(filename);
    string line;

    getline(file, line); // Skip header
    while (getline(file, line))
    {
        stringstream ss(line);
        string a, b, w; // a,b,w->start end and weight

        getline(ss, a, ',');
        getline(ss, b, ',');
        getline(ss, w);

        char start = a[0];
        char end = b[0];
        int weight = stoi(w);

        g.addEdge(start, end, weight);
    }
    file.close();
}

// read vehicles
int read_vehicles(string name, Vehicle vehicles[], int max)
{
    ifstream file(name);
    string line;
    int count = 0;

    getline(file, line);

    while (getline(file, line) && count < max)
    {
        stringstream ss(line);
        string id, start, end;

        getline(ss, id, ',');
        getline(ss, start, ',');
        getline(ss, end);

        vehicles[count].add_vehicle(id, start[0], end[0]);
        count++;
    }
    file.close();
    return count;
}

int read_trafic_signals(string name, Trafic_signal signals[], int max)
{
    ifstream file(name);
    string line;
    int count = 0;

    getline(file, line);
    while (getline(file, line) && count < max)
    {
        stringstream ss(line);
        string node, time;

        getline(ss, node, ',');
        getline(ss, time);

        char n = node[0];
        int t = stoi(time);

        signals[count].add_signal(n, t);
        count++;
    }
    file.close();
    return count;
}

int read_emergency_vehicles(string name, EmergencyVehicle emergencyVehicles[], int max)
{
    ifstream file(name);
    string line;
    int count = 0;

    getline(file, line); // Skip header

    while (getline(file, line) && count < max)
    {
        stringstream ss(line);
        string id, start, end, priority;

        getline(ss, id, ',');
        getline(ss, start, ',');
        getline(ss, end, ',');
        getline(ss, priority);

        emergencyVehicles[count].add_emergency_vehicle(id, start[0], end[0], priority);
        count++;
    }
    file.close();
    return count;
}

void read_road_closures(string filename, Graph &g)
{
    ifstream file(filename);
    string line;

    getline(file, line);
    while (getline(file, line))
    {
        stringstream ss(line);
        string a, b, status;

        getline(ss, a, ',');
        getline(ss, b, ',');
        getline(ss, status);

        char start = a[0];
        char end = b[0];

        Node *temp = g.array[start - 'A'];
        bool check = false;
        // here we updated the road or edge status
        while (temp)
        {
            if (temp->vertx == end)
            {
                temp->status = status;
                check = true;
                break;
            }
            temp = temp->next;
        }
        // if not found in forward then check in reverse

        if (!check)
        {
            temp = g.array[end - 'A'];
            while (temp)
            {
                if (temp->vertx == start)
                {
                    temp->status = status;

                    break;
                }
                temp = temp->next;
            }
        }
    }
    file.close();
}
// Simulate vehicles and count vertex visits
void simulate_vehicles(Graph &g, Vehicle vehicles[], int vehicleCount, int num_vertices)
{
    int vertexVisits[26] = {0}; // Hash table using array

    cout << "\nSimulating vehicle movements:\n";
    for (int i = 0; i < vehicleCount; ++i)
    {
        cout << "\nVehicle " << vehicles[i].ID << ":\n";
        int roadCounts[26][26] = {0};
        g.dijkstra(vehicles[i].Start, vehicles[i].End, roadCounts);

        // Count vertex visits
        for (int j = 0; j < 26; ++j)
        {
            for (int k = 0; k < 26; ++k)
            {
                if (roadCounts[j][k] > 0)
                {
                    vertexVisits[j] += roadCounts[j][k];
                }
            }
        }
    }

    cout << endl;
    cout << "Vertex visit frequencies ->";
    cout << endl;
    for (int i = 0; i < num_vertices; ++i)
    {
        if (vertexVisits[i] > 0)
        {
            cout << char('A' + i) << ": " << vertexVisits[i] << " times\n";
        }
    }
}
int main()
{

    int number_verteces = 26;
    Graph g(number_verteces);
    read_nodes("road.csv", g);
    int roadCounts[26][26] = {0};
    Vehicle vehicles[100];
    Trafic_signal signals[100];
    int signalCount = read_trafic_signals("traffic_signals.csv", signals, 100);

    int choice;
    bool check = true;

    while (check)
    {
        cout << endl;
        cout << "*** Smart Traffic Management System Simulator ***" << endl;

        cout << "1 -> Display City Traffic Network" << endl;
        cout << "2 -> Display Traffic Signal" << endl;
        cout << "3 -> Display Congestion Status" << endl;
        cout << "4 -> Display Blocked Road" << endl;
        cout << "5 -> Handle Emergency Vehicle Routing" << endl;
        cout << "6 -> Block Road due to Accident" << endl;
        cout << "7 -> Simulate Vehicle Routing " << endl;
        cout << "8 -> Display all path " << endl;
        cout << "9 -> Exit Simulation" << endl;
        cout << "Enter your Choice: ";

        cin >> choice;

        if (choice == 1)
        {
            cout << "Displaying City Traffic Network..." << endl;
            g.display_graph();
            cout << endl;
        }
        else if (choice == 2)
        {
            cout << "Displaying Traffic Signal..." << endl;
            for (int i = 0; i < signalCount; ++i)
            {
                signals[i].display();
            }
        }
        else if (choice == 3)
        {
            cout << "Displaying Congestion Status...\n";
            int vehicleCount = read_vehicles("vehicles.csv", vehicles, 100);
            cout << endl;
            cout << "Calculating routes for all vehicles:" << endl;
            for (int i = 0; i < vehicleCount; ++i)
            {
                g.dijkstra(vehicles[i].Start, vehicles[i].End, roadCounts);
            }
            for (int i = 0; i < number_verteces; i++)
            {
                for (int j = i + 1; j < number_verteces; j++)
                {
                    if (roadCounts[i][j] > 0)
                    {
                        cout << char('A' + i) << " -> " << char('A' + j)
                             << ": " << roadCounts[i][j] << " vehicles" << endl;
                    }
                }
            }
        }
        else if (choice == 4)
        {
            cout << "Displaying Blocked Road...\n";
            read_road_closures("road_closures.csv", g);
            g.displayblockroads();
        }
        else if (choice == 5)
        {
            cout << "Routing Emergency Vehicles...\n";
            cout << "Enter the route for emergency vehicle: ";
            char start, end;
            cout << "start: ";
            cin >> start;
            cout << "end: ";
            cin >> end;
            g.dijkstra(start, end, roadCounts);
        }
        else if (choice == 6)
        {
            cout << "Blocking a Road...\n";
            cout << "Enter the road to block: ";
            char start, end;
            cout << "start: ";
            cin >> start;
            cout << "end: ";
            cin >> end;
            g.blocking_road(start, end);
        }
        else if (choice == 7)
        {
            cout << "Simulating Vehicle Routing for All Paths..." << endl;
            int vehicleCount = read_vehicles("vehicles.csv", vehicles, 100);
            simulate_vehicles(g, vehicles, vehicleCount, number_verteces);
        }
        else if (choice == 8)
        {
            cout << "Displaying all path..." << endl;
            cout << "Enter the start point: ";
            char start;
            cin >> start;
            cout << "Enter the end point: ";
            char end;
            cin >> end;
            g.print_all_path(start, end);
        }
        else if (choice == 9)
        {
            cout << "Exiting Simulation...";
            cout << endl;
            check = false;
        }
        else
        {
            cout << "Invalid choice. Please try again";
            cout << endl;
        }
    }

    return 0;
}

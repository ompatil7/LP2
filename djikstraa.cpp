#include <iostream>
using namespace std;

const int INF = 1e9;

int minDistance(int dist[], bool visited[], int V)
{
    int minDist = INF, minIndex = -1;
    for (int v = 0; v < V; ++v)
    {
        if (!visited[v] && dist[v] <= minDist)
        {
            minDist = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void printShortestPaths(int dist[], int V)
{
    cout << "Vertex    Distance from Source\n";
    for (int i = 0; i < V; ++i)
        cout << i << "\t\t" << dist[i] << endl;
}

void dijkstraShortestPath(int graph[][100], int V, int src)
{
    int dist[V];
    bool visited[V] = {false};

    for (int i = 0; i < V; ++i)
        dist[i] = INF;

    dist[src] = 0;

    for (int count = 0; count < V - 1; ++count)
    {
        int u = minDistance(dist, visited, V);
        visited[u] = true;

        for (int v = 0; v < V; ++v)
        {
            if (!visited[v] && graph[u][v] != -1 &&  dist[u] != INF && dist[u] + graph[u][v] < dist[v])

            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printShortestPaths(dist, V);
}

int main()
{
    int V;
    cout << "Enter the number of vertices: ";
    cin >> V;

    int graph[100][100]; // Assuming a maximum of 100 vertices

    cout << "Enter the number of edges: ";
    int E;
    cin >> E;

    cout << "Enter the edges (src dest weight):\n";
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            graph[i][j] = -1; // Initialize all weights to -1

    for (int i = 0; i < E; ++i)
    {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph[src][dest] = weight;
    }   

    int src;
    cout << "Enter the source vertex: ";
    cin >> src;

    dijkstraShortestPath(graph, V, src);

    return 0;
}

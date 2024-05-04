#include <iostream>
using namespace std;

#define INF 1e9

int minDistance(int dist[], bool visited[], int V)
{
    int minDist = INF, minIndex = -1;
    for(int i=0; i<V; i++)
    {
        if(!visited[i] && dist[i] < minDist)
        {
            minDist = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void primsMST(int graph[][100], int V)
{
    int parent[V];
    bool visited[V];
    int dist[V];

    for(int i=0; i<V; i++)
    {
        parent[i] = -1;
        visited[i] = false;
        dist[i] = INF;
    }

    dist[0] = 0;

    for(int count=0 ; count< V-1 ; count++)
    {
        int u = minDistance(dist, visited, V);
        visited[u] = true;
        for(int v=0; v<V ; v++)
        {
            if(!visited[v] && graph[u][v] != -1 && graph[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = graph[u][v];
            }
        }
    }

    cout << "Edge \t Distance" << endl;

    for(int i=1; i<V; i++)
    {
        cout << parent[i] << "-" << i << "\t\t" << graph[i][parent[i]] << endl;
    }
}


int main()
{
    int graph[100][100];
    int V, E;
    cin >> V >> E;
    for(int i=0; i<V; i++)
    {
        for(int j=0; j<V; j++)
        {
            graph[i][j] = -1;
        }
    }

    for(int i=0; i<E; i++)
    {
        int src, dest, wt;
        cin >> src >> dest >> wt;
        graph[src][dest] = wt;
        graph[dest][src] = wt;
    }

    primsMST(graph, V);
}
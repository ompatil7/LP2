// #include <iostream>
// #include <fstream>
// #include <map>
// #include <list>
// #include <queue>
#include <bits/stdc++.h>

using namespace std;

class Graph {
    map<int, list<int>> adjList;
    public:
        void addEdge(int src, int dest)
        {
            adjList[src].push_back(dest);
            adjList[dest].push_back(src);
        }
        void dfs(int v, map<int, bool> &visited)
        {
            visited[v] = true;
            cout << v << " ";
            for(int n: adjList[v])
            {
                if(!visited[n])
                {
                    dfs(n, visited);
                }
            }
        }

        void bfs(queue<int> &q, map<int, bool> &visited)
        {
            if(q.empty())
                return;

            int node = q.front();
            q.pop();

            cout << node << " ";
            for(int n: adjList[node]) {
                if(!visited[n])
                {
                    visited[n] = true;
                    q.push(n);
                }
            }

            bfs(q, visited);
        }
};

int main()
{
    Graph g;
    ifstream infile("input.txt");
    if(!infile.is_open())
    {
        cout << "Error opening file " << endl;
    }
    int V, E;
    infile >> V >> E;

    map<int, bool>visited;
    for(int i=0; i<V; i++)
    {
        visited[i] = false;
    }

    for(int i=0 ; i<E ; i++)
    {
        int src, dest;
        infile >> src >> dest;
        g.addEdge(src, dest);
    }

    int startVertex;
    cout << "Enter the starting vertex: ";
    cin >> startVertex;

    queue<int> q;
    int ch;
    cout << "1 BFS \n 2 DFS \nEnter : ";
    cin >> ch;

    if(ch == 1)
    {
        // for(int i=0; i<V ; i++)
        // {
            if(!visited[startVertex])
            {
                visited[startVertex] = true;
                q.push(startVertex);
                g.bfs(q, visited);
            }
        // }

        cout << "\n";
    }
    else {
        // for(int i=0; i<V; i++)
        // {    
            if(!visited[startVertex])
            {
                g.dfs(startVertex, visited);
            }
        // }
    }

}
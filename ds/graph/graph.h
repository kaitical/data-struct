#include <iostream>
#include <limits.h>
#include <vector>
#include"../queue/queue.h"
using namespace std;

template <typename Tv, typename Te>
class Graph {
public:
    int V;
    vector<Tv>* vertexes;
    vector<vector<Te>>* edges;

    Graph(int v) {
        V = v;
        vertexes = new vector<Tv>(V);
        edges = new vector<vector<Te>>(V, vector<Te>(V));
    }

    void addEdge(int v, int w, Te weight) {
        (*edges)[v][w] = weight;
        (*edges)[w][v] = weight;
    }

    vector<vector<Te>>& getEdges() {
        return *edges;
    }
};

template <typename Tv, typename Te>
void dijkstra(Graph<Tv, Te>& graph, char s, vector<Te>& dist) {
    int index = s - 'a';
    vector<bool> visited(graph.V, false);
    dist[index] = 0;

    for (int i = 0; i < graph.V - 1; ++i) {
        int u = -1;
        for (int j = 0; j < graph.V; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                u = j;
        }

        visited[u] = true;
        for (int v = 0; v < graph.V; ++v) {
            if (!visited[v] && graph.getEdges()[u][v] != 0) {
                dist[v] = min(dist[v], dist[u] + graph.getEdges()[u][v]);
            }
        }
    }
}

template <typename Tv, typename Te>
void prim(Graph<Tv, Te>& graph, char s, vector<Te>& dist, vector<int>& parent) {
    int index = s - 'a';
    vector<bool> visited(graph.V, false);
    dist[index] = 0;
    parent[index] = -1;

    for (int i = 0; i < graph.V - 1; ++i) {
        int u = -1;
        for (int j = 0; j < graph.V; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                u = j;
        }

        visited[u] = true;
        for (int v = 0; v < graph.V; ++v) {
            if (!visited[v] && graph.getEdges()[u][v] != 0 && graph.getEdges()[u][v] < dist[v]) {
                dist[v] = graph.getEdges()[u][v];
                parent[v] = u;
            }
        }
    }
}

template <typename Tv, typename Te>
void BFS(Graph<Tv, Te>& graph, int s) {
    vector<bool> visited(graph.V, false);

    Queue<int> q;
    visited[s] = true;
    q.enqueue(s);

    while (!q.is_empty()) {
        int v = q.front();
        cout << v << " ";
        q.dequeue();

        for (int i = 0; i < graph.V; ++i) {
            if (graph.getEdges()[v][i] != 0 && !visited[i]) {  // 使用getEdges方法获取边及其权重
                visited[i] = true;
                q.enqueue(i);
            }
        }
    }
}

template <typename Tv, typename Te>
void DFSUtil(Graph<Tv, Te>& graph, int v, vector<bool>& visited) {
    visited[v] = true;
    cout << v << " ";

    for (int i = 0; i < graph.V; ++i) {
        if (graph.getEdges()[v][i] != 0 && !visited[i]) {  // 使用getEdges方法获取边及其权重
            DFSUtil(graph, i, visited);
        }
    }
}

template <typename Tv, typename Te>
void DFS(Graph<Tv, Te>& graph, int s) {
    vector<bool> visited(graph.V, false);
    DFSUtil(graph, s, visited);
}
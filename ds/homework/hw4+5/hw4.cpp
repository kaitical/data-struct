#define _CRT_SECURE_NO_WARNINGS 1

#include"../../graph/graph.h"
int main() {
    Graph<char, int> g(7);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 3, 2);
    g.addEdge(2, 4, 2);
    g.addEdge(2, 5, 5);
    g.addEdge(3, 5, 1);
    g.addEdge(3, 6, 1);
    g.addEdge(4, 5, 1);
    g.addEdge(5, 6, 2);

    char source = 'a';
    cout << "BFS traversal: ";
    BFS(g, 0);
    cout << endl;

    cout << "DFS traversal: ";
    DFS(g, 0);
    cout << endl;
    // �������·��(dijkstra)�㷨
    vector<int> dist(g.V, INT_MAX);
    dijkstra(g, source, dist);

    cout << "���·�����£�" << endl;
    for (int i = 0; i < g.V; ++i)
        cout << source << " -> " << char(i + 'a') << ": " << dist[i] << endl;

    cout << endl;

    // ������С֧����(prim)�㷨
    vector<int> parent(g.V, -1);
    prim(g, source, dist, parent);

    cout << "��С֧�������£�" << endl;
    for (int i = 0; i < g.V; ++i) {
        if (parent[i] != -1)
            cout << "(" << char(parent[i] + 'a') << ", " << char(i + 'a') << ")" << endl;
    }

    return 0;
}
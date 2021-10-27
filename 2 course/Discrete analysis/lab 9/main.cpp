/*Хренникова Ангелина
Лабораторная работа №9
Вариант - 7*/

#include <iostream>
#include <climits>
#include <cstring>
#include <queue>
#include <vector>
#include <time.h>

using namespace std;

bool BFS(vector<vector<int>> &graph, int s, int t, vector<int> &parent) {
    
    queue <int> q;
    q.push(s);
    vector<bool> used(graph.size(), false);
    used[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int k = q.front();
        q.pop();

        for (int i = 0; i < graph.size(); i++) {
            if (!used[i] && graph[k][i] > 0) {
                q.push(i);
                parent[i] = k;
                used[i] = true;
            }
        }
    }
    return (used[t]);
}

long long FordFulkerson(vector<vector<int>> &graph, int s, int t) {

    vector<int> parent(t + 1);

    long long maxFlow = 0;

    while (BFS(graph, s, t, parent)) {
        int pathFlow = 1000000001;
        for (int i = t; i != s; i = parent[i]) {
            int k = parent[i];
            pathFlow = min(pathFlow, graph[k][i]);
        }

        for (int i = t; i != s; i = parent[i]) {
            int k = parent[i];
            graph[k][i] -= pathFlow;
            graph[i][k] += pathFlow;
        }

        maxFlow += pathFlow;
    }
    return maxFlow;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1, vector<int> (n + 1));

    int from, to, val;
    for (int j = 0; j < m; ++j) {
        cin >> from >> to >> val;
        graph[from][to] = val;
    }

    cout << FordFulkerson(graph, 1, n) << '\n';

    return 0;
}
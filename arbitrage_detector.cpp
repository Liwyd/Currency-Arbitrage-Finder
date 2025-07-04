#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

struct Edge {
    int u, v;
    double weight;
};

void proccessGraph(int, int);

int main() {
    int n, m;

    while (cin >> n >> m) 
        proccessGraph(n, m);

    return 0;
}

void proccessGraph(int n, int m) {
    vector<string> nodeIdentifiers(n);
    map<string, int> identifiervIndex;

    for (int i = 0; i < n; i++) {
        cin >> nodeIdentifiers[i];
        identifiervIndex[nodeIdentifiers[i]] = i;
    }

    vector<Edge> edges;
    for (int i = 0; i < m; i++) {
        int u1, v1;
        double r;

        cin >> u1 >> v1 >> r;
        edges.push_back({u1 - 1, v1 - 1, -log(r)});
    }

    vector<double> dist(n, 0.0);
    vector<int> parent(n, -1);

    int negativeCycleNode = -1;
    for (int i = 0; i < n; i++) {
        negativeCycleNode = -1;
        for (auto& edge : edges) {
            if (dist[edge.u] + edge.weight < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.weight;
                parent[edge.v] = edge.u;
                negativeCycleNode = edge.v;
            }
        }
    }

    if (negativeCycleNode == -1) {
        cout << "No negative cycle" << endl;
        return;
    }

    int curr = negativeCycleNode;
    for (int i = 0; i < n; i++)
        curr = parent[curr];

    vector<int> cycle;
    for (int v = curr;; v = parent[v]) {
        cycle.push_back(v);
        if (v == curr && cycle.size() > 1) 
            break;
    }

    reverse(cycle.begin(), cycle.end());

    cout << cycle.size() << endl;
    for (int v : cycle)
        cout << v + 1 << " ";
    
    cout << endl;
}
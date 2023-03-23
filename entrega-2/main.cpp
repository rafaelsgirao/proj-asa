#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

//#define uint long unsigned int
//#define uint int

// Struct representing an edge in the graph
struct Edge {
    uint u, v, w;
};

// Comparison function to pass to the sort() function.
// Since we want an MST with the maximum weights, we invert
// the comparison here.
bool compareEdges(const Edge &e1, const Edge &e2) { 
    return e1.w > e2.w; 
}

// Kruskal
vector<Edge> Kruskal(uint V, const vector<Edge> &edges) {
    vector<Edge> minimum_spanning_tree;
    vector<uint> parent(V + 1);
    for (uint i = 1; i <= V; i++) {
        parent[i] = i;
    }
    for (const Edge &e : edges) {
        uint u = e.u;
        uint v = e.v;
        while (u != parent[u]) {
            u = parent[u];
        }
        while (v != parent[v]) {
            v = parent[v];
        }
        if (u != v) {
            minimum_spanning_tree.push_back(e);
            parent[u] = v;
        }
    }
    return minimum_spanning_tree;
}

int main() {
    std::ios::sync_with_stdio(false); // Faster IO
    uint v, e;
    // print
    cin >> v >> e;
    vector<Edge> edges;
    edges.resize(e);
    // Read all edges from input
    for (uint i = 0; i < e; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    // Introsort the edges
    sort(edges.begin(), edges.end(), compareEdges);

    // Run Kruskal
    vector<Edge> minimum_spanning_tree = Kruskal(v, edges);
    uint sum = 0;
    for (const Edge &e : minimum_spanning_tree) {
        // cout << e.u << " " << e.v << " " << e.w << endl;
        sum += e.w;
    }
    cout << sum << endl;
    return 0;
}

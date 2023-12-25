#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int src, dest, weight;
};

struct Subset {
    int parent, rank;
};

bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

class Graph {
    int V; 
    vector<Edge> edges;

public:
    Graph(int vertices) : V(vertices) {}

    void addEdge(int src, int dest, int weight) {
        Edge edge = { src, dest, weight };
        edges.push_back(edge);
    }

    int find(vector<Subset>& subsets, int i) {
        if (subsets[i].parent != i)
            subsets[i].parent = find(subsets, subsets[i].parent);
        return subsets[i].parent;
    }

    void Union(vector<Subset>& subsets, int x, int y) {
        int xroot = find(subsets, x);
        int yroot = find(subsets, y);

        if (subsets[xroot].rank < subsets[yroot].rank)
            subsets[xroot].parent = yroot;
        else if (subsets[xroot].rank > subsets[yroot].rank)
            subsets[yroot].parent = xroot;
        else {
            subsets[yroot].parent = xroot;
            subsets[xroot].rank++;
        }
    }

    void KruskalMST() {
        vector<Edge> result;
        int i = 0, e = 0;
        sort(edges.begin(), edges.end(), compareEdges);
        vector<Subset> subsets(V);
        for (int v = 0; v < V; ++v) {
            subsets[v].parent = v;
            subsets[v].rank = 0;
        }
        while (e < V - 1 && i < edges.size()) {
            Edge next_edge = edges[i++];
            int x = find(subsets, next_edge.src);
            int y = find(subsets, next_edge.dest);
            if (x != y) {
                result.push_back(next_edge);
                Union(subsets, x, y);
                e++;
            }
        }
        cout << "Edges in the Minimum Spanning Tree:\n";
        for (i = 0; i < result.size(); ++i) {
            cout << result[i].src << " - " << result[i].dest << " : " << result[i].weight << "\n";
        }
    }
};
int main() {
    int V = 4; 
    Graph graph(V);
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 6);
    graph.addEdge(0, 3, 5);
    graph.addEdge(1, 3, 15);
    graph.addEdge(2, 3, 4);
    graph.KruskalMST();

    return 0;
}
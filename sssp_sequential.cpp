#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
using namespace std;

struct Edge { int src, dest, weight; };

vector<int> bellmanFord(const vector<Edge>& edges, int nodes, int source) {
    vector<int> dist(nodes, INT_MAX);
    dist[source] = 0;

    for (int i = 0; i < nodes - 1; i++) {
        for (const Edge& e : edges) {
            if (dist[e.src] != INT_MAX && dist[e.dest] > dist[e.src] + e.weight) {
                dist[e.dest] = dist[e.src] + e.weight;
            }
        }
    }
    return dist;
}

int main() {
    ifstream file("road_network.txt");
    int nodes, edges;
    file >> nodes >> edges;

    vector<Edge> edgeList;
    for (int i = 0; i < edges; i++) {
        Edge e;
        file >> e.src >> e.dest >> e.weight;
        edgeList.push_back(e);
    }

    int source = 0;  // Change this to any node
    vector<int> distances = bellmanFord(edgeList, nodes, source);

    // Print shortest path from source to node 10 (example)
    cout << "Distance from " << source << " to 10: " << distances[10] << endl;

    return 0;
}

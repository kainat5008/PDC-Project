#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <omp.h>
using namespace std;

struct Edge { int src, dest, weight; };

vector<int> bellmanFord(const vector<Edge>& edges, int nodes, int source) {
    vector<int> dist(nodes, INT_MAX);
    dist[source] = 0;

    for (int i = 0; i < nodes - 1; i++) {
        bool updated = false;

        #pragma omp parallel for reduction(||:updated)
        for (size_t j = 0; j < edges.size(); j++) {
            const Edge& e = edges[j];
            if (dist[e.src] != INT_MAX && dist[e.dest] > dist[e.src] + e.weight) {
                #pragma omp critical
                {
                    if (dist[e.dest] > dist[e.src] + e.weight) {
                        dist[e.dest] = dist[e.src] + e.weight;
                        updated = true;
                    }
                }
            }
        }

        if (!updated) break;  // Early exit if no updates
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

    int source = 0;
    vector<int> distances = bellmanFord(edgeList, nodes, source);

    cout << "Distance from " << source << " to 10: " << distances[10] << endl;
    return 0;
}

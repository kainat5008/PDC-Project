#include <mpi.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

struct Edge { int src, dest, weight; };

void computeSSSP(int rank, const vector<Edge>& localEdges, int totalNodes) {
    vector<int> dist(totalNodes, INT_MAX);
    dist[0] = 0;  // Source node (change if needed)

    // Bellman-Ford (simplified)
    for (int i = 0; i < totalNodes - 1; i++) {
        for (const Edge& e : localEdges) {
            if (dist[e.src] != INT_MAX && dist[e.dest] > dist[e.src] + e.weight) {
                dist[e.dest] = dist[e.src] + e.weight;
            }
        }
        MPI_Allreduce(MPI_IN_PLACE, dist.data(), totalNodes, MPI_INT, MPI_MIN, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        cout << "Distance from 0 to 10: " << dist[10] << endl;
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Read partition-specific edges
    string filename = "partition_" + to_string(rank) + ".txt";
    ifstream file(filename);
    vector<Edge> localEdges;
    int src, dest, weight;
    while (file >> src >> dest >> weight) {
        localEdges.push_back({src, dest, weight});
    }

    // Get total node count from the METIS header
    ifstream metisFile("graph_fixed.graph");
    int totalNodes, totalEdges;
    metisFile >> totalNodes >> totalEdges;

    computeSSSP(rank, localEdges, totalNodes);
    MPI_Finalize();
    return 0;
}

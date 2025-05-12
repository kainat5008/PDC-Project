__kernel void sssp_update(
    __global const int* offsets,
    __global const int* edges,
    __global const int* weights,
    __global int* distances,
    const int num_nodes)
{
    int tid = get_global_id(0);
    if (tid >= num_nodes) return;

    int start = offsets[tid];
    int end = offsets[tid+1];

    for (int i = start; i < end; i++) {
        int neighbor = edges[i];
        int new_dist = distances[tid] + weights[i];
        
        // Atomic update
        atomic_min(&distances[neighbor], new_dist);
    }
}

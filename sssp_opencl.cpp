#include <iostream>
#include <fstream>
#include <vector>

#include <OpenCL/cl.hpp>  // Alternative path
// Helper to load OpenCL kernel source
std::string loadKernel(const char* filename) {
    std::ifstream in(filename);
    return std::string(std::istreambuf_iterator<char>(in), 
                      std::istreambuf_iterator<char>());
}

int main() {
    // 1. Set up OpenCL
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    cl::Device device = cl::Device::getDefault();
    cl::Context context(device);
    cl::CommandQueue queue(context, device);

    // 2. Load and compile kernel
    std::string kernel_code = loadKernel("sssp_kernel.cl");
    cl::Program program(context, kernel_code);
    program.build("-cl-std=CL1.2");

    // 3. Load graph data (CSR format)
    std::ifstream file("road_network.txt");
    int nodes, edges;
    file >> nodes >> edges;
    
    std::vector<int> offsets(nodes+1), edges_dest(edges), edges_weight(edges);
    // ... (CSR conversion code here) ...

    // 4. Create GPU buffers
    cl::Buffer d_offsets(context, CL_MEM_READ_ONLY, sizeof(int)*(nodes+1));
    cl::Buffer d_edges(context, CL_MEM_READ_ONLY, sizeof(int)*edges);
    cl::Buffer d_weights(context, CL_MEM_READ_ONLY, sizeof(int)*edges);
    cl::Buffer d_distances(context, CL_MEM_READ_WRITE, sizeof(int)*nodes);

    // 5. Transfer data to GPU
    queue.enqueueWriteBuffer(d_offsets, CL_TRUE, 0, sizeof(int)*(nodes+1), offsets.data());
    // ... (other transfers) ...

    // 6. Set up kernel
    cl::Kernel kernel(program, "sssp_update");
    kernel.setArg(0, d_offsets);
    kernel.setArg(1, d_edges);
    kernel.setArg(2, d_weights);
    kernel.setArg(3, d_distances);
    kernel.setArg(4, nodes);

    // 7. Execute kernel
    cl::NDRange global(nodes);
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, global, cl::NullRange);

    // 8. Read results
    std::vector<int> distances(nodes);
    queue.enqueueReadBuffer(d_distances, CL_TRUE, 0, sizeof(int)*nodes, distances.data());

    std::cout << "Distance to node 10: " << distances[10] << std::endl;
    return 0;
}

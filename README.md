
# Parallel Dynamic SSSP Updater  
**Implementation and Analysis of Parallel Graph Algorithms Using MPI, OpenMP, and METIS**  

## 📌 Project Overview  
This project implements a **parallel algorithm for updating Single-Source Shortest Paths (SSSP)** in large-scale dynamic networks, based on the paper:  
> *[A Parallel Algorithm Template for Updating SSSP in Large-Scale Dynamic Networks](https://doi.org/10.1109/TPDS.2021.3084096)*  
> (IEEE TPDS 2022).  

**Key Features:**  
- 🚀 **Parallel Framework:** Combines MPI (inter-node) and OpenMP (intra-node) for scalability.  
- 🔄 **Dynamic Updates:** Efficiently handles edge insertions/deletions without full recomputation.  
- 📊 **METIS Integration:** Partitions graphs for distributed memory processing.  

**Target Applications:**  
- Transportation networks (real-time traffic updates)  
- Social network analysis (dynamic interactions)  

---


---

## ✅ Phase 1 Status (Completed)  
**Deliverables:**  
1. **Literature Review:**  
   - Summarized paper contributions, algorithm, and results
2. **Parallelization Strategy:**  
   - Designed MPI/OpenMP/METIS workflow
3. **Presentation Slides:**  
   - Covered problem, algorithm, and implementation plan 

---

## ✅ Phase 2 Status  
## ⚡ Parallelization Strategy  
### 1. MPI (Inter-Node)  
- **Graph Partitioning:** METIS divides the graph into `k` balanced subgraphs (1 per MPI process).  
- **Communication:** Sync boundary vertices after updates using `MPI_Allreduce`.  

### 2. OpenMP (Intra-Node)  
- Parallelize edge processing and vertex updates with dynamic scheduling:  
  ```cpp
  #pragma omp parallel for schedule(dynamic)
  for (auto v : AffectedVertices) { ... }

  # Single-Source Shortest Path (SSSP) in Dynamic Road Networks

This repository contains the code and documentation for a project focused on efficiently solving the Single-Source Shortest Path (SSSP) problem in dynamic road networks. The project explores and analyzes various approaches, with a particular emphasis on parallel computing techniques to handle the dynamic nature of these networks.

## Overview

Traditional SSSP algorithms are designed for static graphs. However, real-world road networks experience frequent changes in traffic conditions, leading to modifications in travel times (edge weights) and even the addition or removal of roads. Recomputing the shortest paths from scratch after each change is computationally expensive for large networks.

This project addresses this challenge by investigating and implementing algorithms that can incrementally update shortest path information when changes occur, minimizing the computational cost.

## Report

A detailed report on the project, including the problem statement, approaches, implementations, and analysis, can be found in [Report.pdf](Report.pdf). The report covers:

* An introduction to the SSSP problem and the challenges posed by dynamic road networks.
* A discussion of different approaches to address the SSSP problem in dynamic environments.
* Details of the implemented algorithms, including a sequential implementation using the Bellman-Ford algorithm.
* An exploration of parallel computing techniques such as MPI and OpenCL for improving performance.
* A discussion of a promising hybrid approach combining MPI and OpenMP for large-scale dynamic road networks.
* Key considerations for efficient handling of dynamic updates in parallel systems, including graph partitioning, data distribution, communication minimization, incremental updates, and load balancing.

## Approaches and Implementations Explored

The project explored the following approaches and their implementations:

1.  *Sequential Implementation:*
    * Algorithm: Bellman-Ford algorithm (as mentioned in the report snippet).
    * [Further details about the implementation would be added here if available in the full report or code.]

2.  *Parallel Implementations:*
    * *MPI (Message Passing Interface):* Explored for distributing the graph across multiple machines.
    * *OpenCL (Open Computing Language):* Investigated for leveraging the parallelism of GPUs.
    * *Hybrid MPI and OpenMP:* A combined approach for distributed and shared-memory parallelism, identified as the most promising for large-scale dynamic networks.

## Key Considerations for Dynamic Updates

The project highlights the following crucial aspects for efficiently handling dynamic updates in parallel SSSP algorithms for road networks:

* *Graph Partitioning:* Utilizing tools like METIS to partition the graph effectively.
* *Data Distribution:* Strategically distributing graph data across MPI processes.
* *Communication:* Minimizing communication overhead, especially global synchronization, between processes.
* *Incremental Updates:* Developing algorithms to update shortest paths efficiently upon edge weight changes.
* *Load Balancing:* Ensuring even workload distribution across computing resources.

## Further Research

The report concludes that further research and development are necessary to optimize parallel algorithms and data structures specifically for dynamic road networks.

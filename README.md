
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

## ⚡ Parallelization Strategy  
### 1. MPI (Inter-Node)  
- **Graph Partitioning:** METIS divides the graph into `k` balanced subgraphs (1 per MPI process).  
- **Communication:** Sync boundary vertices after updates using `MPI_Allreduce`.  

### 2. OpenMP (Intra-Node)  
- Parallelize edge processing and vertex updates with dynamic scheduling:  
  ```cpp
  #pragma omp parallel for schedule(dynamic)
  for (auto v : AffectedVertices) { ... }

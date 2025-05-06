from collections import defaultdict
import sys

def main():
    print("Reading partitions...", file=sys.stderr)
    with open("graph_fixed.graph.part.4") as f:
        partitions = [int(line.strip()) for line in f]

    print("Processing edges...", file=sys.stderr)
    files = [open(f"partition_{i}.txt", "w") for i in range(4)]
    with open("road_network.txt") as f:
        for line in f:
            src, dest, weight = map(int, line.strip().split())
            files[partitions[src]].write(f"{src} {dest} {weight}\n")

    for f in files:
        f.close()
    print("Done!", file=sys.stderr)

if __name__ == "__main__":
    main()

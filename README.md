# Directed Graph Acyclicity Checker (C++)

## Overview
This project determines whether a **directed graph is acyclic** and, if not, to **detect and print the first cycle found**.

The program:
- Reads a graph from an input file
- Represents it using an **adjacency matrix**
- Checks for cycles using a **Sink Elimination algorithm**
- If a cycle exists, finds and prints it using **Depth First Search (DFS)**

---

## Features

### 1. Graph Representation
- Uses an **adjacency matrix**
- Dynamically maps node values (e.g., 1, 2, 3) to internal indices
- Maintains reverse mapping to display original node values

### 2. Input Parsing
- Reads graph edges from `input.txt`
- Automatically:
  - Extracts all unique nodes
  - Maps them to indices
  - Builds the adjacency matrix

### 3. Acyclicity Check (Sink Elimination)
- Repeatedly removes **sink nodes** (nodes with no outgoing edges)
- If:
  - All nodes are removed → graph is **acyclic**
  - No sink is found at some step → graph contains a **cycle**

### 4. Cycle Detection (DFS)
- Uses Depth First Search with:
  - `visited` array
  - `recursion stack`
  - `parent tracking`
- Detects **back edges**, which indicate cycles
- Reconstructs and prints the **first cycle found**

---
## Input Format
The input file (`input.txt`) should contain **directed edges**, one per line:
1 2
2 3
3 1
3 4
Meaning that there are edges from vertex 1 to vertex 2 etc.

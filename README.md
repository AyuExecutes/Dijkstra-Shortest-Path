# Dijkstra's Algorithm in C++
This program implements **Dijkstra's Algorithm** to calculate the shortest paths from a source vertex to all other vertices in a weighted, directed graph. This program is represented using an adjacency list.

## Features
- Implement Dijkstra's Algorithm using a min-heap.
- Validates edge weights to ensure they are within the specified range (1 to 99).
- Outputs the shortest path distances from the source vertex to all other vertices.

## Input Format
1. First Line: `n m`
- `n` is the number of vertices in the graph.
- `m` is the number of edges in the graph.
2. Next `m` Lines: Each line represents an edge as `u v w`
- `u` is the source vertex of the edge.
- `v` is the destination vertex of the edge.
- `w` is the weight of the edge (1 ≤ `w` ≤ 99)

## Output Format
- A single line containing the shortest path distances from source vertex (vertex `0`) to all other vertices.
- If a vertex is not reachable from the source, the output will display **"Infinity"** for that vertex.

## Example
### Input (File: `input.in`)
        6 8
        0 1 4
        0 3 2
        1 2 99
        1 5 2
        2 5 1
        3 1 1
        4 1 3
        5 2 3

### Output
        0 3 8 2 infinity 5

### Explanation
The shortest path from vertex 0:
- To vertext 1: `0 -> 3 -> 1`. Distance of 3.
- To vertex 2: `0 -> 3 -> 1 -> 5 -> 2`. Distance of 8.
- To vertex 3: `0 -> 3`. Distance of 2.
- To vertex 4: `Infinity`. Not reachable.
- To vertex 5: `0 -> 3 -> 1 -> 5`. Distance of 5. 

## Compilation and Execution
1. Compile the program:  
`g++ -o DijkstraShortestPath.cpp`
2. Run the program:  
`cat input.in | ./ DijkstraShortestPath`

## Limitation
- This implementation assumes the graph is directed.
- It does not support negative edge weights.
- The source vertex is always assumed to be vertex `0`.

## Contributing
Contributions are welcome, if you have any suggestions for improving the code or documentation:
1. Fork the repository.
2. Make your changes.
3. Submit a pull request.

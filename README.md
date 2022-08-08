# MSTfinder


this program finds weights of MST in undirected graphs

the graph should be in a file

Usage:

```
./main graph.txt
```

the file should contain:

1. two numbers: n - number of vertexes, m - number of edges
2. a list of valid edges, each in the form u v w:

   * u - a vertex between 1-n
   * v - a vertex between 1-n
   * w - weight of edge (whole numbers)
3. two numbers u v:

   - this is an edge to remove from the graph
   - does not have to be an edge in the previous list

the program runs kruskal once

then prim

then removes the edge in 3 and runs kruskal again

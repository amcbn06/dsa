# Tree Algorithms

This folder contains implementations of algorithms for tree structures.

## Implementations

### Lowest Common Ancestor (LCA)

A few methods for finding the lowest common ancestor of two nodes in a tree:

1. Binary lifting
2. Sparse table on Euler Tour
3. Segment Tree on Euler Tour
4. Tarjan's Offline LCA algorithm
5. ??? (online)

### Heavy Light Decomposition (HLD)

Heavy-light decomposition is a technique that allows us to effectively solve many problems that come down to queries on a tree. It works by splitting the tree into several paths so that we can reach the root vertex from any node v by traversing **at most $\log{}n$ paths**. It is clear that if we find such a decomposition for any tree, it will allow us to reduce certain single queries of the form _“calculate something on the path from $a$ to $b$”_ to several queries of the type _“calculate something on the segment_ $[l, r]$ _of the_ $k^{th}$ _path”_.

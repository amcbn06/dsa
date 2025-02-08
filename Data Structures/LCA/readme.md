# Lowest Common Ancestor queries on trees
These are a few techniques i encountered when solving problems related to finding the lowest common ancestor (lca) of two nodes in a tree. \
The complexities are written in the notation < $O(f(n)),\ O(g(n))$ >, meaning that the data structure requires $O(f(n))$ construction time and $O(g(n))$ query time.

## I. Binary lifting
##### Time complexity: < $O(n\log{}n), O(\log{}n)$ >
##### Space complexity: $O(n\log{}n)$
Description: By precomputing for each node $u$ in $anc[u][p]$ it's $2^p$-th ancestor, we can use these links to traverse the tree in logarithmic time. By precomputing the entry time and exit time for each node $u$, we can check if a node $v$ is in the subtree of node $u$ by checking if the range $[entry(v),\ exit(v)]$ is included in the range $[entry(u),\ exit(u)]$. Using these two precalculations, we can find the lowest common ancestor of $u$ and $v$ by progressively raising $v$ up by a powers of 2 as long as it does not become an ancestor of $u$. Then if we raise $v$ one more time we reach the lca.

Code: [binary_lifting.cpp](binary_lifting.cpp)

###### Note: this technique can be used also for finding the K-th ancestor of any node
###### Note: this technique can be modified for different variations of this problem, such as finding the distance from $u$ to $v$, the sum of values on the edges or nodes from $u$ to $v$ (also max, gcd, maximum subarray sum, etc.)


## II. Sparse table on Euler Tour
##### Time complexity: < $O(n\log{}n), O(1)$ >
Description: \
Code: 

## III. Segment Tree on Euler Tour
##### Time complexity: < $O(n), O(\log{}n)$ >
Description: \
Code: 

## IV. ??? (online)
##### Time complexity: < $O(n), O(1)$ >
Description: \
Code: 

## V. DSU on DFS Traversal (offline)
##### Time complexity: < $O(n), O(1)$ >
Description: \
Code: 

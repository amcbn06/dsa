# Lowest Common Ancestor queries on trees
These are a few techniques i encountered when solving problems related to finding the lowest common ancestor (lca) of two nodes in a tree. \
The complexities are written in the notation < $O(f(n)),\ O(g(n))$ >, meaning that the data structure requires $O(f(n))$ construction time and $O(g(n))$ query time.

<br>

## I. Binary lifting
##### Time complexity: < $O(n\log{}n), O(\log{}n)$ >
##### Space complexity: $O(n\log{}n)$

Description: By precomputing for each node $u$ in $anc[u][p]$ it's $2^p$-th ancestor, we can use these links to traverse the tree in logarithmic time. By precomputing the entry time and exit time for each node $u$, we can check if a node $v$ is in the subtree of node $u$ by checking if the range $[entry(v),\ exit(v)]$ is included in the range $[entry(u),\ exit(u)]$. Using these two precalculations, we can find the lowest common ancestor of $u$ and $v$ by progressively raising $v$ up by a powers of 2 as long as it does not become an ancestor of $u$. Then if we raise $v$ one more time we reach the lca.

Code: [binary_lifting.cpp](binary_lifting.cpp)

Sample implementation (k-th ancestor): [CSES - Company Queries I](https://cses.fi/problemset/task/1687) [[code](https://cses.fi/paste/d2774ac15d38f9edb789ae/)] \
Sample implementation (lowest common ancestor): [CSES - Company Queries II](https://cses.fi/problemset/task/1688) [[code](https://cses.fi/paste/75811c09a01863b4b789c8/)]

###### Note: this technique can be used also for finding the K-th ancestor of any node
###### Note: this technique can be modified for different variations of this problem, such as finding the distance from $u$ to $v$, the sum of values on the edges or nodes from $u$ to $v$ (also max, gcd, maximum subarray sum, etc.)

<br>

## II. Sparse table on Euler Tour
##### Time complexity: < $O(n\log{}n), O(1)$ >
##### Space complexity: $O(n\log{}n)$

Description: By computing the Euler Tour of the tree and than RMQ on it (instead of the minimum value we pick the node with the smaller depth) we can compute in $O(1)$ the lca for any two nodes $u$ and $v$.

Code: [euler_tour_rmq.cpp](euler_tour_rmq.cpp)

Sample implementation: [CSES - Company Queries II](https://cses.fi/problemset/task/1688) [[code](https://cses.fi/paste/c443ef5110f3b49eb789d9/)]

###### Note: this technique is very useful when the number of queries is greater than the number of nodes, as the time complexity of each query is $O(1)$

<br>

## III. Segment Tree on Euler Tour
##### Time complexity: < $O(n), O(\log{}n)$ >
##### Space complexity: $O(n\log{}n)$

Description: Based on the same reasoning as above, but instead of RMQ using Segment Tree, we can do the precomputing in $O(n)$, but the time complexity of the queries will be logarithmic. 

Code: [euler_tour_segment_tree.cpp](euler_tour_segment_tree.cpp)

Sample implementation: [CSES - Company Queries II](https://cses.fi/problemset/task/1688) [[code](https://cses.fi/paste/fb098c5263fc282fb789e4/)]

###### Note: this technique is very useful when the number of nodes is greater than the number of queries, as the time complexity of the precalculation is $O(n)$

<br>

## IV. ??? (online)
##### Time complexity: < $O(n), O(1)$ >

Description:

Code:

<br>

## V. DSU on DFS Traversal (offline)
##### Time complexity: < $O(n), O(1)$ >

Description:

Code:

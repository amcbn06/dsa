# Fenwick Tree / Binary Indexed Tree (BIT) 

The Fenwick Tree is an efficient data structure that computes dynamic prefix sum queries and point updates in $O(\log{n})$ time. By leveraging binary index properties, it hierarchically partitions data into ranges, allowing efficient computation of cumulative sums.

#### Key features:
* Time complexity:
    * Point updates in $O(\log{n})$
    * Prefix queries in $O(\log{n})$
    * Build in $O(n)$
* Space complexity: $O(n)$

## How it works
For an array $A$ of $N$ numbers, we'll keep an array $t$ of size $N$ representing the Fenwick Tree. Each position $i$ will store the sum of the values from $A$ in the interval $[i - 2^{lsb(i)} + 1, i]$, where $lsb(i)$ is the least set bit in the binary representation of $i$. In other words, $\ t[i]\ = \sum\limits_{j\ =\ i\ -\ 2^{lsb(i)}\ +\ 1}^{i} A[i]$


Based on this, we can quickly figure out a implementation for the prefix sum query. Before that though, it turns out that using bitwise operations we can express $lsb(i)$ simply as  $i$ & $-i$. Therefore the query method would look something like:

```cpp
int get(int i) {
    int sum = 0;
    for (; i > 0; i -= i & -i) {
        sum += t[i];
    }
}
```

Based on this we can even find the sum of a range by doing some prefix sum magic:

```cpp
int get(int l, int r) {
    // sum[l...r] = prefix[r] - prefix[l - 1]
    return get(r) - get(l - 1); 
}
```

What about updates? When we change the value at a position i in $A$, we must update the values of all $t[j]$ such that $i \in [j - 2^{lsb(j)} + 1, j]$. How do we do that? Due to _reasons that are left for the reader to discover_, the code ends up looking similar to the query one:

```cpp
void add(int i, int x) {
    for (; i <= N; i += i & -i) {
        t[i] += x;
    }
}
```

### Advantages:
* **Simpler implementation** than other alternatives (ex. Segment Tree)
* **Faster** than other alternatives due to the **small constant factor**
* **Lower memory overhead**: for an array of size $N$ the Fenwick Tree needs an array of size exactly $N$, as opposed to between $2N$ and $4N$ for a Segment Tree

### Disadvantages:
* **Restricted functionality**: Only works with invertible operations when it comes to range queries (e.g., addition, XOR). Non-invertible operations (max/min, multiplication, GCD) are supported only for prefix queries; lacks versatility compared to Segment Trees, which natively can handle complex operations (range min/max, bulk updates via lazy propagation).

* **Inefficient Range Operations**: Directly computes prefix sums only. Arbitrary range sums require indirect calculations (e.g., prefix[j] - prefix[i-1]), complicating non-additive operations; also updating intervals requires workarounds (e.g., difference arrays or dual Fenwick Trees), adding overhead compared to Segment Trees with built-in lazy propagation.

* **Indexing Complexity**: While the Segment Tree's main idea of splitting intervals into halves seems pretty intuitive, the Fenwick Tree relies on binary indexing tricks (e.g., least significant bit manipulation), which can be unintuitive and harder to understand.

###### Note: As you can see, as the complexity of a problem increases, the disavantages start outweighing the advantages; that's why the Fenwick Tree is a very useful data structure only for specific problems and usually when the time and/or memory limits are tight.

## Use Cases

### 1. Classic Fenwick Tree: point add, range sum

Let's take [this problem](https://judge.yosupo.jp/problem/point_add_range_sum). This is the trivial use case of the Fenwick Tree; using the implementation provided below, the code would look something like [this](https://judge.yosupo.jp/submission/269678).

Code: [prefix_sum.cpp](prefix_sum.cpp)



### 2. Range add, point query

We have an array $A$ of $N$ numbers and we want to perform two types of operations of it:
1. for each index $i$ in range $[l, r]$, perform $a[i] = a[i] + x$
2. what is the value at position $i$?

This is basically [this problem](https://cses.fi/problemset/task/1651). To solve we can use another array $B$ where we'll store only the added values from the queries of type 1. Now we take advantage of the concept of a [difference array](https://www.geeksforgeeks.org/difference-array-range-update-query-o1/); if we regard $B$ as a difference array, _"add_ $x$ _on range_ $[l, r]$_"_ becomes _"add_ $x$ _to_ $B[l]$ _and substract_ $x$ _from_ $B[r + 1]$_"_. Then the queries of type 2 can be answered by adding $A[i]$ and $\sum\limits_{j\ =\ 1}^{i} B[j]$. Now all we have to do is use a Fenwick Tree for array $B$. Bonus points to the reader if they can "merge" arrays $A$ and $B$ (store just the Fenwick Tree, without array $A$). [Here](https://cses.fi/paste/6217dc35a34e6911b9b96e/)'s a sample implementation.

Code: [range_add.cpp](range_add.cpp)



### 3. Range add, range query

Code: ***#todo***



### 4. Prefix minimum

Code: ***#todo***



### 5. 2D Fenwick Tree

Code: ***#todo***



### Additional problems
1. [perm - ONI 2024 Baraj Seniori](https://kilonova.ro/problems/2669?list_id=1082)

### Additional resources
1. [cp-algorithms/fenwick](https://cp-algorithms.com/data_structures/fenwick.html)
2. [Brilliant](https://brilliant.org/wiki/fenwick-tree/) - a very begginer-friendly explaination
3. [Algorithmica](https://en.algorithmica.org/hpc/data-structures/segment-trees/#fenwick-trees) - a very detailed explaination + comparison with segment tree (that includes benchmarks)

# TreeWalk

## Main Functions
1. **SetBinaryTree()**: Pre-processes the binary tree and builds an internal map to make `FindMinPath()` efficient.
2. **FindMinPath()**: Finds the lowest common ancestor (LCA), then calculates the upward and downward paths.

## Time Complexity
- `SetBinaryTree()`: O(n)
- `FindMinPath()`: O(h), where h is the height of the tree.

## TODO
- Implement Euler Tour + RMQ for cases with a large number of queries.  
  This will make `FindMinPath()` more efficient (O(1) per query), though memory usage will increase to O(n log n).

## Usage
- cmake .
- make TreeWalkTest 
- ./TreeWalkTest

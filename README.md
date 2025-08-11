# TreeWalk

## Main Functions
1. **SetBinaryTree()**: Pre-processes the binary tree and builds an internal map to make `FindMinPath()` efficient.
2. **FindMinPath()**: Finds the lowest common ancestor (LCA), then calculates the upward and downward paths.

## Class
Simple Parent Pointer, Binary Lifting and Euler Tour + RMQ are written by AI
SimpleTreeWalk is refined from Simple Parent Pointer.

## Time Complexity
||SetBinaryTree()|FindMinPath()|
|Simple Parent Pointer|O(n)|O(h), where h is the height of the tree.|
|SimpleTreeWalk|O(n)|O(h)|
|Binary Lifting|O(NlogN)|O(logh)|
|Euler Tour + RMQ|O(NlogN)|O(1)|

## Usage
```sh
cd TreeWalk
cmake .
make 
./TreeWalkTest
./TreeWalkPerformanceTest 
```
TreeWalkTest is to check the correctness.
TreeWalkTest is to check the performance.


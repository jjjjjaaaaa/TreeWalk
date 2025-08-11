# TreeWalk

## Main Functions
1. **SetBinaryTree()**: Pre-processes the binary tree and builds an internal map to make `FindMinPath()` efficient.
2. **FindMinPath()**: Finds the lowest common ancestor (LCA), then calculates the upward and downward paths.
3. ** Clear()**: To clear the member data 

## Class
Simple Parent Pointer, Binary Lifting and Euler Tour + RMQ are written by AI
SimpleTreeWalk is refined from Simple Parent Pointer.

## Time Complexity
||SetBinaryTree()|FindMinPath()|
| ------------- | ------------- | ------------- |
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

TreeWalkPerformanceTest  is to check the performance.

## Performance
### case 1 : Balanced Tree
||SetBinaryTree()|FindMinPath()| Clear()|
| ------------- | ------------- | ------------- | ------------- |
|Simple Parent Pointer|1369.7|11.4|241.2|
|SimpleTreeWalk|1339.7|8.7|238.6|
|Binary Lifting|6458.2|17.3|960.6|
|Euler Tour + RMQ|9375.6|18.6|909.8|

### case 2 : Stick Tree
||SetBinaryTree()|FindMinPath()| Clear()|
| ------------- | ------------- | ------------- | ------------- |
|Simple Parent Pointer|730.3|136.1|120.0|
|SimpleTreeWalk|622.0|86.5|120.9|
|Binary Lifting|2441.2|88.9|458.6|
|Euler Tour + RMQ|3406.9|108.66|347.3|

## Conclusion
The time complexity for FindMinPath() in the above list is only calculate the Lowest Common Ancestor. However the time to find the path costs a lot.
It points out the complexity is one thing, and the actual processing time is another.

SimpleTreeWalk works similiar with SimpleParentPointerWalk.
SimpleTreeWalk works more efficiently because it uses std::unordered_map to store the the id mapping with node and depth, 
then the depth could be got in O(1), better than SimpleParentPointerWalk.




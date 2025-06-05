# Data_Structure_Project: AVL Tree Implementation

**Disclaimer**: The project contains text in romanian, some parts may need to be translated.

This is a repo of a project that I make for my Data Structures and Algorithms class

The project is required to be in C++

---

## Definition

An AVL tree is a type of self-balancing binary search tree (BST) in which the height difference (balance factor) between the left and right subtrees of any node is at most 1.

## Key Characteristics

- Named after its inventors: Adelson-Velsky and Landis (1962).
- Maintains O(log n) time for insertion, deletion, and search.
- Uses rotations (single or double) to rebalance after insertions or deletions.
- Guarantees balanced height, unlike plain BSTs which can become skewed.

## Balance factor

For a node `N`, the **balance factor** is:

```cpp
balanceFactor(N) = height(N.left) - height(N.right)
```

- Must always be -1, 0, or +1 for AVL condition to hold.
- If not, rotations are performed to fix it.

## Rotations

| Imbalance Type   | Rotation Type         |
| ---------------- | --------------------- |
| Left-Left (LL)   | Right Rotation        |
| Right-Right (RR) | Left Rotation         |
| Left-Right (LR)  | Left + Right Rotation |
| Right-Left (RL)  | Right + Left Rotation |

## Time Complexities

| Operation | Time Complexity |
| --------- | --------------- |
| Search    | O(log n)        |
| Insert    | O(log n)        |
| Delete    | O(log n)        |



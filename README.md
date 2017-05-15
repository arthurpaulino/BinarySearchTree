BinarySearchTree
================

An implementation of the *(unbalanced) binary search tree* data structure written in C++. The constructor requires a pointer to a comparation function.

* Instantiation

```cpp
//int compar(int a, int b) is a comparation function
BinarySearchTree<int> *bst = new BinarySearchTree<int>(compar);
```

* Insertion

```cpp
int x;
bst->add(x);
```

* Search

```cpp
bool contains = bst->has(x);
```

* Remotion

```cpp
bool removed = bst->remove(x);
```

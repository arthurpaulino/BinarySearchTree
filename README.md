BinarySearchTree
================

An implementation of the *(unbalanced) binary search tree* data structure written in C++. The constructor requires two functions:

1. A function that returns a *key*, given certain *content*;
2. A function that compares two *keys* and returns an integer
⋅⋅⋅equal *0* if the keys match
...greater than *0* if the first *key* is "bigger" than the first one
...less than *0* otherwise

* Instantiation

```cpp
int compareKeys_usability(string nameA, string nameB) {
	return strcmp(nameA.c_str(),nameB.c_str());
}

string getKey_usability(Person *person) {
	return person->name;
}
.
.
.
BinarySearchTree<Person*,string> *bst = new BinarySearchTree<Person*,string>(getKey,compareKeys);
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

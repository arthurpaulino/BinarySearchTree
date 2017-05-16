BinarySearchTree
================

An implementation of the *(unbalanced) binary search tree* data structure written in C++. The constructor requires **two types** (the type of the keys and the type of the stored content) and **two functions**:
1. A function that returns a *key*, given certain *content*
2. A function that compares two *keys* and returns an integer that is
   * equal *0* if the keys match
   * greater than *0* if the first *key* is "bigger" than the first one
   * less than *0* otherwise

* Instantiation
```cpp
int compareKeys(string nameA, string nameB) {
	return strcmp(nameA.c_str(),nameB.c_str());
}

string getKey(Person *person) {
	return person->name;
}

int main() {
	BinarySearchTree<Person*,string> *bst = new BinarySearchTree<Person*,string>(getKey,compareKeys);
```
* Insertion
```cpp
Person *p = new Person("name", 23);
bool added = bst->addContent(p);
```
* Search
```cpp
bool contains = bst->hasKey("name");
```
* Remotion
```cpp
bool removed = bst->removeByKey("name");
```
**The following methods may throw `std::invalid_argument` exceptions if the keys cannot be found**
* Search and return content
```cpp
Person *p = bst->getContentByKey("name");
```
* Search, remove and return content
```cpp
Person *p = bst->extractContentByKey("name");
```
**Warning**: modifying *content* in a way that changes the comparisions with the *key* generated from it will most likely crash the *binary search tree* stability. In the `example.c` file, there's nothing wrong with changing the *age* of the persons, since *age* is not used for comparisions.

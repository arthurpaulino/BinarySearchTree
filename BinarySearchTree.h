#ifndef H_BINARYSEARCHTREE
#define H_BINARYSEARCHTREE

#include <ctime>
#include <cstdlib>
#include <stdexcept>

template <typename C, typename K>
class BinarySearchTree {

private:

	class Node {
	public:
		C content;
		Node *left, *right;
		Node(C content):content(content),left(0),right(0){}
	};
	Node *root;
	K (*getKey)(C);
	int (*compareKeys)(K, K);
	
	Node *chopBiggestFromLeft(Node* node) {
		Node **nodePtrToChild = &(node->left), *child = node->left;
		while (child->right != 0) {
			node = child;
			nodePtrToChild = &(node->right);
			child = child->right;
		}
		*nodePtrToChild = child->left;
		return child;		
	}
	
	Node *chopSmallestFromRight(Node* node) {
		Node **nodePtrToChild = &(node->right), *child = node->right;
		while (child->left != 0) {
			node = child;
			nodePtrToChild = &(node->left);
			child = child->left;
		}
		*nodePtrToChild = child->right;
		return child;		
	}
	
	void clear(Node* node) {
		if (node != 0) {
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}
	
public:
	
	BinarySearchTree(K (*getKey)(C), int (*compareKeys)(K, K)):getKey(getKey),compareKeys(compareKeys),root(0){srand(time(0));}
	
	bool hasKey(K key) {
		Node* node = root;
		int comparation;
		while (node != 0) {
			comparation = compareKeys(getKey(node->content), key);
			if (comparation == 0) return true;
			if (comparation > 0) node = node->left;
			else node = node->right;
		}
		return false;
	}
	
	bool addContent(C content) {
		if (root == 0) {
			root = new Node(content);
			return true;
		}
		Node *parent = root, *child = 0;
		int comparation;
		while (true) {
			comparation = compareKeys(getKey(parent->content), getKey(content));
			if (comparation == 0) return false;
			if (comparation > 0) child = parent->left;
			else child = parent->right;
			if (child == 0) {
				if (comparation > 0) parent->left = new Node(content);
				else parent->right = new Node(content);
				return true;
			}
			parent = child;
		}
	}
	
	bool removeByKey(K key) {
		if (root == 0) return false;
		Node **parentPtr = &root, *node = root;
		int comparation;
		while (true) {
			comparation = compareKeys(getKey(node->content), key);
			if (comparation == 0) {
				if (node->left == 0 && node->right == 0) *parentPtr = 0;
				else if (node->left == 0) *parentPtr = node->right;
				else if (node->right == 0) *parentPtr = node->left;
				else {
					Node *substitute;
					if (rand()%2) {
						substitute = chopBiggestFromLeft(node);
						substitute->right = node->right;
						substitute->left = node->left;
						*parentPtr = substitute;
					}
					else {
						substitute = chopSmallestFromRight(node);
						substitute->left = node->left;
						substitute->right = node->right;
						*parentPtr = substitute;
					}
				}
				return true;
			}
			if (comparation > 0) {
				parentPtr = &(node->left);
				node = node->left;
			}
			else {
				parentPtr = &(node->right);
				node = node->right;
			}
			if (node == 0) return false;
		}
	}
	
	C getContentByKey(K key) {
		Node* node = root;
		int comparation;
		while (node != 0) {
			comparation = compareKeys(getKey(node->content), key);
			if (comparation == 0) return node->content;
			if (comparation > 0) node = node->left;
			else node = node->right;
		}
		throw std::invalid_argument("Key not found.");
	}
	
	C extractByKey(K key) {
		if (root == 0) throw std::invalid_argument("Key not found.");
		Node **parentPtr = &root, *node = root;
		int comparation;
		while (true) {
			comparation = compareKeys(getKey(node->content), key);
			if (comparation == 0) {
				if (node->left == 0 && node->right == 0) *parentPtr = 0;
				else if (node->left == 0) *parentPtr = node->right;
				else if (node->right == 0) *parentPtr = node->left;
				else {
					Node *substitute;
					if (rand()%2) {
						substitute = chopBiggestFromLeft(node);
						substitute->right = node->right;
						substitute->left = node->left;
						*parentPtr = substitute;
					}
					else {
						substitute = chopSmallestFromRight(node);
						substitute->left = node->left;
						substitute->right = node->right;
						*parentPtr = substitute;
					}
				}
				return node->content;
			}
			if (comparation > 0) {
				parentPtr = &(node->left);
				node = node->left;
			}
			else {
				parentPtr = &(node->right);
				node = node->right;
			}
			if (node == 0) throw std::invalid_argument("Key not found.");
		}
	}
	
	virtual ~BinarySearchTree() {
		clear(root);
	}
};

#endif


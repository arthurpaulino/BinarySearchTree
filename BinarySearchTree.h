#ifndef H_BINARYSEARCHTREE
#define H_BINARYSEARCHTREE

#include <ctime>
#include <cstdlib>

template <class T>
class BinarySearchTree {

private:

	class Node {
	public:
		T content;
		Node *left, *right;
		Node(T content):content(content),left(0),right(0){}
	};
	Node *root;
	int (*f)(T, T);
	
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
	
	BinarySearchTree(int (*f)(T, T)):root(0),f(f){srand(time(0));}
	
	bool has(T value) {
		Node* iterNode = root;
		int compar;
		while (iterNode != 0) {
			compar = f(iterNode->content, value);
			if (compar == 0) return true;
			if (compar > 0) iterNode = iterNode->left;
			else iterNode = iterNode->right;
		}
		return false;
	}
	
	bool add(T value) {
		if (root == 0) {
			root = new Node(value);
			return true;
		}
		Node *parent = root, *child = 0;
		int compar;
		while (true) {
			compar = f(parent->content, value);
			if (compar == 0) return false;
			if (compar > 0) child = parent->left;
			else child = parent->right;
			if (child == 0) {
				if (compar > 0) parent->left = new Node(value);
				else parent->right = new Node(value);
				return true;
			}
			parent = child;
		}
	}
	
	bool remove(T value) {
		if (root == 0) return false;
		Node **parentPtr = &root, *node = root;
		int compar;
		while (true) {
			compar = f(node->content, value);
			if (compar == 0) {
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
			if (compar > 0) {
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
	
	virtual ~BinarySearchTree() {
		clear(root);
	}
};

#endif

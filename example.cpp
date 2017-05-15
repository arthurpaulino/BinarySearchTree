#include <ctime>
#include <cstdlib>
#include <cstdio>
#include "BinarySearchTree.h"

int counter;

int compar(int a, int b) {
	counter++;
	return a-b;
}

int main() {
	srand(time(NULL));
	BinarySearchTree<int> *bst = new BinarySearchTree<int>(compar);
	
	int n = 23;
	int N = 1<<n;
	
	counter = 0;	
	for (int i = 0; i < N; i++) bst->add(rand());
	printf("Average of %.2lf comparations to add 2^%d numbers.\n", (double)counter/(double)N, n);
	
	counter = 0;	
	for (int i = 0; i < N; i++) bst->has(rand());
	printf("Average of %.2lf comparations to search 2^%d numbers.\n", (double)counter/(double)N, n);
	
	counter = 0;
	for (int i = 0; i < N; i++) bst->remove(rand());
	printf("Average of %.2lf comparations to remove 2^%d numbers.\n", (double)counter/(double)N, n);
	
	return 0;
}

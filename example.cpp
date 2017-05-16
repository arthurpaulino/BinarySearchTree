#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include "BinarySearchTree.h"

using namespace std;

int getKey_efficiency(int content) {
	return content;
}

int counter;
int compareKeys_efficiency(int keyA, int keyB) {
	counter++;
	return keyA-keyB;
}

class Person {
public:
	string name;
	int age;
	Person(string name, int age):name(name),age(age){}
};

string getKey_usability(Person *person) {
	return person->name;
}

int compareKeys_usability(string nameA, string nameB) {
	return strcmp(nameA.c_str(),nameB.c_str());
}

int main() {
	
	printf("Testing efficiency.\n");

	srand(time(NULL));
	
	BinarySearchTree<int,int> *bst_efficiency = new BinarySearchTree<int,int>(getKey_efficiency,compareKeys_efficiency);
	
	int n = 20;
	int N = 1<<n;
	
	counter = 0;	
	for (int i = 0; i < N; i++) bst_efficiency->addContent(rand());
	printf("Average of %.2lf comparations to add 2^%d numbers.\n", (double)counter/(double)N, n);
	
	counter = 0;	
	for (int i = 0; i < N; i++) bst_efficiency->hasKey(rand());
	printf("Average of %.2lf comparations to search 2^%d numbers.\n", (double)counter/(double)N, n);
	
	counter = 0;
	for (int i = 0; i < N; i++) bst_efficiency->removeByKey(rand());
	printf("Average of %.2lf comparations to remove 2^%d numbers.\n", (double)counter/(double)N, n);
	
	delete bst_efficiency;
	
	printf("\nShowing usability.\n");
	
	BinarySearchTree<Person*,string> *bst_usability = new BinarySearchTree<Person*,string>(getKey_usability,compareKeys_usability);
	
	Person *p1 = new Person("ana", 21),
		*p2 = new Person("boris", 23),
		*p3 = new Person("carl", 22),
		*p4 = new Person("darwin", 24);
	
	bst_usability->addContent(p3);
	bst_usability->addContent(p1);
	bst_usability->addContent(p2);
	bst_usability->addContent(p4);
	
	if (!bst_usability->hasKey("sean")) printf("'sean' has not been found\n");
	if (bst_usability->hasKey("ana")) printf("'ana' has been found\n");
	
	bst_usability->removeByKey("ana");
	if (!bst_usability->hasKey("ana")) printf("'ana' has not been found\n");
	
	Person *p = bst_usability->getContentByKey("boris");
	printf("boris is %d years old.\n", p->age);
	if (bst_usability->hasKey("boris")) printf("'boris' has been found\n");
	
	p = bst_usability->extractByKey("carl");
	printf("carl is %d years old.\n", p->age);
	if (!bst_usability->hasKey("carl")) printf("'carl' has not been found\n");
	
	try {
		p = bst_usability->getContentByKey("carl");
	} catch (const std::invalid_argument& e) {
		printf("Exception caught: %s\n",e.what());
	}
	
	return 0;
}

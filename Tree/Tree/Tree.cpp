#include "Tree.hpp"
#include <vector>

int compare(int a, int b) {
	return (int)(a < b);
}

typedef int (*cmp_ptr)(int a, int b);

int main() {
	std::vector<int> v;
	cmp_ptr comp = compare; // why it gets me warnings?
	Tree<int, int, cmp_ptr>T((cmp_ptr)comp); // there
	T.addNode(1, 10);
	int a = T.getValue(1);
	T.getValue(1) = 12; // doesn't work properly
	T.removeNode(1);
	for (auto elem : T) {
		v.push_back(elem);
	}
	return 0;
}
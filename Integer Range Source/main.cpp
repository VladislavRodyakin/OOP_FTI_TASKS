#include <iostream>
#include <string>
#include "Integer Range Source.h"

int main() {
	
		for (auto a : Range<int>(1, 23, 4)) {
			std::cout << (a) << std::endl;
		}
	return 0;
}
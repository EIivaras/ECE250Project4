#include <iostream>
#include "Quadratic_hash_table.h"

int main() {
	Quadratic_hash_table<int> quad_hash(5);

	std::cout << "////// BASIC TESTS //////" << std::endl << std::endl;;

	std::cout << "Size: " << quad_hash.size() << std::endl;
	std::cout << "Capacity: " << quad_hash.capacity() << std::endl;
	std::cout << quad_hash << std::endl << std::endl;

	std::cout << "////// SIMPLE INSERT AND ERASE TESTS //////" << std::endl << std::endl;
	std::cout << "Inserting 1, 2, and 3." << std::endl;
	quad_hash.insert(1);
	quad_hash.insert(2);
	quad_hash.insert(3);
	std::cout << quad_hash << std::endl;
	std::cout << "Erasing 3, 2, and 1." << std::endl;
	quad_hash.erase(3);
	quad_hash.erase(2);
	quad_hash.erase(1);
	std::cout << quad_hash << std::endl << std::endl << std::endl;

	std::cout << "////// INSERT AND ERASE WITH OVERLAPPING HASH VALUE TESTS //////" << std::endl << std::endl;
	std::cout << "Inserting 63, 1, and 32" << std::endl;
	quad_hash.insert(63);
	std::cout << quad_hash << std::endl;
	quad_hash.insert(1);
	std::cout << quad_hash << std::endl;
	quad_hash.insert(32);
	std::cout << quad_hash << std::endl;
	std::cout << "Erasing 32, 63, and 1" << std::endl;
	quad_hash.erase(32);
	std::cout << quad_hash << std::endl;
	quad_hash.erase(63);
	std::cout << quad_hash << std::endl;
	quad_hash.erase(1);
	std::cout << quad_hash << std::endl << std::endl;
}

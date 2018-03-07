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
	std::cout << "Inserting 64, 0, and 32" << std::endl;
	quad_hash.insert(64);
	std::cout << quad_hash << std::endl;
	quad_hash.insert(0);
	std::cout << quad_hash << std::endl;
	quad_hash.insert(32);
	std::cout << quad_hash << std::endl;
	std::cout << "Erasing 32, 64, and 0" << std::endl;
	quad_hash.erase(32);
	std::cout << quad_hash << std::endl;
	quad_hash.erase(64);
	std::cout << quad_hash << std::endl;
	quad_hash.erase(0);
	std::cout << quad_hash << std::endl << std::endl;

	std::cout << "////// ADVANCED TESTS //////" << std::endl << std::endl;

	Quadratic_hash_table<int> quad_hash2(5);

	std::cout << "Insert 31" << std::endl;
	quad_hash2.insert(31);
	std::cout << quad_hash2 << std::endl;
	std::cout << "Insert 191" << std::endl;
	quad_hash2.insert(191);
	std::cout << quad_hash2 << std::endl;
	std::cout << "Index of 31: " << quad_hash2.bin(31) << std::endl;
	std::cout << "Index of 191: " << quad_hash.bin(191) << std::endl;
	std::cout << "Insert 159" << std::endl;
	quad_hash2.insert(159);
	std::cout << quad_hash2 << std::endl;
	std::cout << "Erase 159" << std::endl;
	quad_hash2.erase(159);
	std::cout << quad_hash2 << std::endl;
	std::cout << "Check if 159 is still in: " << quad_hash2.member(159) << std::endl;
}

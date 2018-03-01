/*****************************************
* Instructions
*  - Replace 'uwuserid' with your uWaterloo User ID
*  - Select the current calendar term and enter the year
*  - List students with whom you had discussions and who helped you
*
* uWaterloo User ID:  zwalford@uwaterloo.ca
* Submitted for ECE 250
* Department of Electrical and Computer Engineering
* University of Waterloo
* Calender Term of Submission:  (Winter) 2018
*
* By submitting this file, I affirm that
* I am the author of all modifications to
* the provided code.
*
* The following is a list of uWaterloo User IDs of those students
* I had discussions with in preparing this project:
*    -
*
* The following is a list of uWaterloo User IDs of those students
* who helped me with this project (describe their help; e.g., debugging):
*    -
*****************************************/

#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include "ece250.h"

enum bin_state_t { UNOCCUPIED, OCCUPIED, ERASED };

template <typename Type>
class Quadratic_hash_table {
private:
	int count; // Amount of objects in array
	int power;
	int array_size;
	int mask;
	Type *array;
	bin_state_t *occupied;

	int hash(Type const &) const;

public:
	// Basics

	Quadratic_hash_table(int = 5);
	~Quadratic_hash_table();

	// Accessors

	int size() const;
	int capacity() const;
	double load_factor() const;
	bool empty() const;
	bool member(Type const &) const;
	Type bin(int) const;

	void print() const; // const on the end of a fxn means it doesn't create/edit/delete any data

	// Mutators

	void insert(Type const &);
	bool erase(Type const &);
	void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<(std::ostream &, Quadratic_hash_table<T> const &);
};

/////////////////////////////////////////////////////////////
// Quadratic Has Table Private Member Functions
/////////////////////////////////////////////////////////////

template <typename Type>
int Quadratic_hash_table<Type>::hash(Type const &) const {
	// Implementation required
}

/////////////////////////////////////////////////////////////
// Quadratic Has Table Public Member Functions
/////////////////////////////////////////////////////////////

template <typename Type>
Quadratic_hash_table<Type>::Quadratic_hash_table(int m) :
	count(0), power(m),
	array_size(1 << power),
	mask(array_size - 1),
	array(new Type[array_size]),
	occupied(new bin_state_t[array_size]) {

	for (int i = 0; i < array_size; ++i) {
		occupied[i] = UNOCCUPIED;
	}
}

template <typename Type>
Quadratic_hash_table<Type>::~Quadratic_hash_table() {
	clear();
}

template <typename Type>
int Quadratic_hash_table<Type>::size() const {
	return count;
}

template <typename Type>
int Quadratic_hash_table<Type>::capacity() const {
	return array_size;
}

template <typename Type>
double Quadratic_hash_table<Type>::load_factor() const {
	return count/array_size;
}

template <typename Type>
bool Quadratic_hash_table<Type>::empty() const {
	return count == 0;
}

template <typename Type>
bool Quadratic_hash_table<Type>::member(Type const &) const {
	// Implementation Required
	return false;
}

template <typename Type>
Type Quadratic_hash_table<Type>::bin(int) const {
	// Implementation Required
	Type x = 1; // Temporary for compilation purposes
	return x; // Temporary for compilation purposes
}

template <typename Type>
void Quadratic_hash_table<Type>::print() const {
	// Implementation Required
}

template <typename Type>
void Quadratic_hash_table<Type>::insert(Type const &) {
	// Implementation Required
}

template <typename Type>
bool Quadratic_hash_table<Type>::erase(Type const &) {
	// Implementation Required
	return false;
}

template <typename Type>
void Quadratic_hash_table<Type>::clear()  {
	count = 0;
	power = 0;
	array_size = 0;
	array = nullptr;
	occupied = nullptr;
}

/////////////////////////////////////////////////////////////
// Quadratic Has Table Friend Functions
/////////////////////////////////////////////////////////////

template <typename T>
std::ostream &operator<<(std::ostream &out, Quadratic_hash_table<T> const &hash) {
	for (int i = 0; i < hash.capacity(); ++i) {
		if (hash.occupied[i] == UNOCCUPIED) {
			out << "- ";
		}
		else if (hash.occupied[i] == ERASED) {
			out << "x ";
		}
		else {
			out << hash.array[i] << ' ';
		}
	}

	return out;
}

#endif

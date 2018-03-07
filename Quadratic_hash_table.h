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

#ifndef QUADRATIC_HASH_TABLE_H
#define QUADRATIC_HASH_TABLE_H

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
int Quadratic_hash_table<Type>::hash(Type const & value) const {
	int index = static_cast<int>(value);
	int result = index % mask; // can't do index % array_size because then you could get 16 as your index!
	if (result < 0) {
		result += mask;
	}
	return result;
}

/////////////////////////////////////////////////////////////
// Quadratic Has Table Public Member Functions
/////////////////////////////////////////////////////////////

template <typename Type>
Quadratic_hash_table<Type>::Quadratic_hash_table(int m) :
	count(0), power(m), // hash table is created with 2^m bins
	array_size(1 << power), // so, since left shifting is multiplying the number by 2, the array_size can be calculated from 1*(2*# of left shifts)
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
	int initial_index = hash(value); // The initial index that we would IDEALLY like to insert our object into, returned by the hash fxn
	int index = initial_index; // The index where we will ACTUALLY insert our value into
	int previous = initial_index; // will store the previous value
	for (int i = 1; i < array_size - 1; i++) {
		if (occupied[index] == UNOCCUPIED) { // If we reach an unoccupied slot in our search, then the value must never have been inserted
			return false; // thus, we return false
		}
		else { // otherwise, the slot is either OCCUPIED or ERASED
			if (array[index] == value) {
				return true; // return true if we've found the value
			}
			index = (previous + i) % (array_size - 1); // Make sure we mod 15, so we wrap back around if adding i gives us a value greater than array_size - 1
			previous = index; // set previous AFTER we calculate the new index, otherwise previous and index will be the same
		}
	}
	return false; // if we made it out of the for loop, the array is full and the object doesn't exist in it
}

template <typename Type>
Type Quadratic_hash_table<Type>::bin(int n) const {
	return array[n];
}

template <typename Type>
void Quadratic_hash_table<Type>::print() const {
	// Implementation Required
}

template <typename Type>
void Quadratic_hash_table<Type>::insert(Type const & value) {
	int initial_index = hash(value); // The initial index that we would IDEALLY like to insert our object into, returned by the hash fxn
	int index = initial_index; // The index where we will ACTUALLY insert our value into
	int previous = initial_index; // will store the previous value
	for (int i = 1; i < array_size - 1; i++) {
		if (occupied[index] != OCCUPIED) {
			array[index] = value;
			occupied[index] = OCCUPIED;
			return;
		}
		else {
			if (array[index] == value) { // if the value is already in the quadratic hash table
				return; // do nothing (exit fxn)
			}
			// TODO: IS THE BELOW FXN FOR INDEX CORRECT?! If it was just + i it would be linear probing, yeah?
			index = (previous + i) % (array_size - 1); // Make sure we mod 15, so we wrap back around if adding i gives us a value greater than array_size - 1
			previous = index; // set previous AFTER we calculate the new index, otherwise previous and index will be the same
		}
	}
	throw overflow(); // If we made it out of the for loop, the array must be full, so we throw an overflow exception
}

template <typename Type>
bool Quadratic_hash_table<Type>::erase(Type const & value) {
	int initial_index = hash(value); // The initial index that we would IDEALLY like to insert our object into, returned by the hash fxn
	int index = initial_index; // The index where we will ACTUALLY insert our value into
	int previous = initial_index; // will store the previous value
	for (int i = 1; i < array_size - 1; i++) {
		if (occupied[index] == UNOCCUPIED) { // If we reach an unoccupied slot in our search, then the value must never have been inserted
			return false; // thus, we return false
		}
		else { // otherwise, the slot is either OCCUPIED or ERASED
			if (array[index] == value) {
				occupied[index] = ERASED; // all we need to do is set the value at the value's index in occupied[] to be ERASED- 
				                          // just like with a stack, we don't actually need to clear the values,
				                          // as insert will insert into any index marked as unoccupied AND erased,
				                          // which, in the latter case, will just overwrite the previous value
				return true; // return true on successful erase
			}
			index = (previous + i) % (array_size - 1); // Make sure we mod 15, so we wrap back around if adding i gives us a value greater than array_size - 1
			previous = index; // set previous AFTER we calculate the new index, otherwise previous and index will be the same
		}
	}
	return false; // if we made it out of the for loop, the array is full and the object doesn't exist in it
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

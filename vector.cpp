#ifndef __VECTOR_CPP__
#define __VECTOR_CPP__

#include "vector.h"

#include <stdexcept>

using namespace custom;

template <class T> vector<T>::vector(){
			this->capacity = 1;
			this->contents = new T[this->capacity];
			this->Size = 0;
}
template <class T> vector<T>::~vector(){
	delete[] this->contents;
}
template <class T> T & vector<T>::at(size_t pos){
	if (pos < Size){
		return this->contents[pos];
	}else{
		throw std::runtime_error("Outside bonds");
	}
}
template <class T> size_t vector<T>::size() const{
	return this->Size;
}
template <class T> void vector<T>::clear(){
	this->Size = 0;
}
template <class T> void vector<T>::push_back(const T & data){
	if (this ->Size == this->capacity){
		this->change_capacity(this->capacity * 2);
	}
	this->contents[this->Size] = data;
	this->Size++;
}
template <class T> T vector<T>::pop_back(){
	if (this->Size){
		return this->contents[--(this->Size)];
	}else{
		throw std::runtime_error("Nothing to pop");
	}
}
template <class T> void vector<T>::change_capacity(size_t capacity){
	if (this->capacity > capacity){
		throw std::runtime_error("New capacity smaller than old");
	}else{
		T * contents = new T [capacity];
		for(size_t i = 0; i < this->Size; i++){
			contents[i] = this->contents[i];
		}
		delete[] this->contents;
		this->contents = contents;
		this->capacity = capacity;
	}
}

template <class T> vector<T>::iterator::iterator(){
	this->parent = NULL;
	this->initialized = false;
}
template <class T> vector<T>::iterator::iterator(const iterator & newit){
	this->parent = newit.parent;
	this->pos = newit.pos;
	this->at_end = newit.pos;
	this->initialized = newit.initialized;
}
template <class T> T & vector<T>::iterator::operator*(){
	if (this->initialized){
		return parent->at(this->pos);
	}else{
		throw std::runtime_error("Iterator not initialized");
	}
}
template <class T> void vector<T>::iterator::operator++(){
	if (this->initialized){
		if (this->at_end){
			throw std::runtime_error("Iterator at end");
		}else{
			this->pos++;
			this->at_end = (this->pos == this->parent->size());
		}
	}else{
		throw std::runtime_error("Iterator not initialized");
	}
}
#endif	//	__VECTOR_CPP__

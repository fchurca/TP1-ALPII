#ifndef __VECTOR_CPP__
#define __VECTOR_CPP__

#include "vector.h"

#include <stdexcept>

namespace custom{

	template <class T> vector<T>::vector(){
				this->capacity = 1;
				this->contents = new T[this->capacity];
				this->Size = 0;
	}
	template <class T> vector<T>::~vector(){
		delete[] this->contents;
		this->contents = NULL;
	}
	template <class T> T & vector<T>::at(unsigned long pos){
		if (pos < Size){
			return this->contents[pos];
		}else{
			throw std::runtime_error("Outside bonds");
		}
	}
	template <class T> unsigned long vector<T>::size() const{
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
	template <class T>
		void vector<T>::insert(const vector<T>::iterator & it, const T & data){
		if (!it.initialized){
			throw std::runtime_error("Iterator not initialized");
		}else if (it.parent != this){
			throw std::runtime_error("Wrong iterator parent");
		}else if (it.pos > this->Size){
			throw std::runtime_error("Outside bonds");
		}else{
			this->push_back(data);
			for(unsigned long i = this->Size - 1; i > it.pos; i--){
				T aux = this->at(i);
				this->at(i) = this->at(i-1);
				this->at(i-1) = aux;
			}
		}
	}
	template <class T> void vector<T>::change_capacity(unsigned long capacity){
		if (this->capacity > capacity){
			throw std::runtime_error("New capacity smaller than old");
		}else{
			T * contents = new T [capacity];
			for(unsigned long i = 0; i < this->Size; i++){
				contents[i] = this->contents[i];
			}
			delete[] this->contents;
			this->contents = contents;
			this->capacity = capacity;
		}
	}
}
#endif	//	__VECTOR_CPP__

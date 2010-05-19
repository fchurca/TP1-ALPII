#ifndef __LIST_CPP__
#define __LIST_CPP__

#include "list.h"

#include <stdexcept>

namespace custom{
//**************************************
// list::iterator methods
//******************
// list::iterator::operator*()
//	Indirection
	template <class T>
	T & list<T>::iterator::operator*(){
		if(this->initialized){
			return pos->data;
		}else{
			throw std::runtime_error("Iterator not initialized");
		}
	}
//******************
// list::iterator::operator->()
//	Member by indirection
	template <class T>
	T * list<T>::iterator::operator->(){
		if(this->initialized){
			return &(pos->data);
		}else{
			throw std::runtime_error("Iterator not initialized");
		}
	}
//******************
// list::iterator::operator!=(const iterator &)
//	Not equal to
	template <class T>
	bool list<T>::iterator::operator!=(const list<T>::iterator & newit){
		return ! ((*this) == newit);
	}
//******************
// list::iterator::operator==(const iterator &)
//	Equal to
	template <class T>
	bool list<T>::iterator::operator==(const list<T>::iterator & newit){
		if (!(this->initialized || newit.initialized)){
			throw std::runtime_error("Iterator not initialized");
		}else if (this->parent != newit.parent){
			throw std::runtime_error("Different iterator parents");
		}else if (this->at_end && newit.at_end){
			return true;
		}else{
			return this->pos == newit.pos;
		}
	}

	template <class T> list<T>::list(){
		this->first = this->last = NULL;
		this->Size = 0;
	}
	template <class T> list<T>::~List(){
		this->clear();
	};

	template <class T> unsigned long list<T>::size() const{
		return this->Size;
	};

	template <class T> void list<T>::push_back(const T & data){
		node * to_add = new node(data, NULL);
		if (this->last){
			this->last->next = to_add;
		}else{
			this->first = to_add;
		}
		this->last = to_add;
		this->Size++;
	};

	template <class T> T list<T>::pop_front(){
		if (this->first){
			T ret = this->first->data;
			node * aux = this->first;
			this->first = this->first->next;
			delete aux;
			this->Size--;
			return ret;
		}else{
			throw std::runtime_error("Nothing to pop");
		}
	};

	template <class T> void list<T>::clear(){
		while(this->first){
			this->pop_front();
		}
	}

}

#endif	//	__LIST_CPP__

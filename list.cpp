#ifndef __LIST_CPP__
#define __LIST_CPP__

#include "list.h"

#include <stdexcept>

namespace custom{

	template <class T> list<T>::list(){
		this->first = this->last = NULL;
		this->Size = 0;
	}
	template <class T> list<T>::~List(){
		this->clear();
	};

	template <class T> size_t list<T>::size() const{
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

#ifdef LIST_DEBUG

#include <iostream>

int main(int argc, char **argv){
	custom::list<int> mylist;
	std::cout << mylist.size() << std::endl;
	mylist.push_back(43);
	std::cout << mylist.size() << std::endl;
	mylist.push_back(44);
	mylist.push_back(45);
	std::cout << mylist.pop_front() << std::endl;
	std::cout << mylist.size() << std::endl;
	return EXIT_SUCCESS;
}

#endif	//	LIST_DEBUG

#endif	//	__LIST_CPP__

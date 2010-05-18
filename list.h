#ifndef __LIST_H__
#define __LIST_H__
#include <cstdlib>

#include <stdexcept>

namespace custom{
	template <class T> class list{
	public:
		class node{
			node * next;
			T data;
		public:
			node(){
				this->next = NULL;
			}
			node(const T & data, node * next){
				this->data = data;
				this->next = next;
			}
		friend class list;
		};
		list();
		~list();
		size_t size() const;
		void clear();
		void push_back(const T & data);
		T pop_front();
	protected:
		size_t Size;
		node
			* first,
			* last;
	};
};
#include "list.cpp"
#endif	//	__LIST_H__

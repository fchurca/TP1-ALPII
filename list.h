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
			node();
			node(const T & data, node * next);
		friend class list;
		};
		class iterator{
			list * parent;
			node * pos;
			bool at_end;
			bool initialized;
		public:
			iterator(){
				this->initialized = false;
			}
			iterator(const iterator & newit){
				this->parent = newit.parent;
				this->pos = newit.pos;
				this->at_end = newit.at_end;
				this->initialized = newit.initialized;
			}
			T & operator*(){
				if(this->initialized){
					return pos->data;
				}else{
					throw std::runtime_error("Iterator not initialized");
				}
			}
			T * operator->(){
				if(this->initialized){
					return &(pos->data);
				}else{
					throw std::runtime_error("Iterator not initialized");
				}
			}
			bool operator!=(const iterator & newit){
				return ! ((*this) == newit);
			}
			bool operator==(const iterator & newit){
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
			void operator++(){
				if (this->initialized){
					if (this->at_end){
						throw std::runtime_error("Iterator at end");
					}else{
						this->pos = this->pos->next;
						if (! (this->pos)){
							this->at_end = true;
						}
					}
				}else{
					throw std::runtime_error("Iterator not initialized");
				}
			}
			void operator++(int){
				++(*this);
			}
		friend class list;
		};
		iterator begin(){
			iterator ret;
			ret.parent = this;
			ret.at_end = !(this->first);
			ret.initialized = true;
			ret.pos = this->first;
			return ret;
		}
		iterator end(){
			iterator ret;
			ret.parent = this;
			ret.at_end = true;
			ret.initialized = true;
			ret.pos = NULL;
			return ret;
		}
		list();
		~list();
		size_t size() const;
		void clear();
		void push_back(const T & data);
		T pop_front();
		void insert(const iterator & it, const T & data){
			if (!it.initialized){
				throw std::runtime_error("Iterator not initialized");
			}else if (it.parent != this){
				throw std::runtime_error("Wrong iterator parent");
			}else if (it.at_end || ! this->last){
				push_back(data);
			}else if (it.pos == this->first){
				node * to_add = new node(data, this->first);
				this->first = to_add;
				if (! this->last){
					this->last = to_add;
				}
			}else{
				node * to_add = new node(it.pos->data, it.pos->next);
				it.pos->next = to_add;
				it.pos->data = data;
			}
		}
	protected:
		size_t Size;
		node
			* first,
			* last;
	};
};
#include "list.cpp"
#endif	//	__LIST_H__

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <cstdlib>

#include <stdexcept>

namespace custom{
	template <class T> class vector{
		size_t
			Size,
			capacity;
		T * contents;
	public:
		class iterator{
			vector * parent;
			size_t pos;
			bool at_end;
			bool initialized;
		public:
			iterator();
			iterator(const iterator & newit);
			T & operator*();
			T * operator->(){
				if(this->initialized){
					return &(this->parent->at(pos));
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
			void operator++();
			void operator++(int){
				++(*this);
			}
		friend class vector;
		};
		vector();
		~vector();
		iterator begin(){
			iterator ret;
			ret.parent = this;
			ret.at_end = !this->Size;
			ret.initialized = true;
			ret.pos = 0;
			return ret;
		}
		iterator end(){
			iterator ret;
			ret.parent = this;
			ret.at_end = true;
			ret.initialized = true;
			ret.pos = this->Size;
			return ret;
		}
		T & at(size_t pos);
		size_t size() const;
		void clear();
		void push_back(const T & data);
		T pop_back();
		void insert(const iterator & it, const T & data);
		void change_capacity(size_t capacity);
	};
}

#include "vector.cpp"

#endif	//	__VECTOR_H__

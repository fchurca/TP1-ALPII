#include "vector.h"

namespace custom{
	template <typename T> class stack : vector<T>{
	public:
		unsigned long size() const{
			return this->vector<T>::size();
		}
		void clear(){
			this->vector<T>::clear();
		}
		void push(const T & data){
			this->vector<T>::push_back(data);
		}
		T pop(){
			return this->vector<T>::pop_back();
		}
		T & top(){
			return this->vector<T>::at(this->size()-1);
		}
	};
};

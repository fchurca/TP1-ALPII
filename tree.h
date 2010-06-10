/*******************************************************************************
 *	list.h
 *	Librería de árbol n-ario
 *	Implementación de árbol:      Fiona González Lisella (Padrón 91454)
*******************************************************************************/
# include "list.h"
namespace custom {
	template<typename T> class tree{
		T _data;
		list<tree> _children; 
	public:
		T & data(){
			return this->_data;
		}
		list<tree> & children(){
			return this->_children;
		}
		void add_child(const T& data){
			tree to_add;
			to_add._data = data;
			this->_children.push_back(to_add);
		}
/*		unsigned size(){
			unsigned ret = 1;
			list<tree>::iterator
				it = this->children().begin(),
				end = 	this->children().end();
			while(it != end){
				ret += it->size();
				it++;
			}
			return ret;
		}
*/	};
}

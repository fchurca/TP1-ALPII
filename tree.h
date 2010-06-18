/*******************************************************************************
 *	tree.h
 *	Librería de árbol n-ario
 *	Implementación de árbol:      Fiona González Lisella (Padrón 91454)
*******************************************************************************/
# include "list.h"

using namespace std;

namespace custom {
	template<typename T> class tree{
	protected:
		T _data;
		list<tree> _children; 
	public:
		T & data(){
			return this->_data;
		}
		list<tree> & children(){
			return this->_children;
		}
		void clear(){
			this->children().clear();
		}
		void add_child(const T& data){
			tree to_add;
			to_add._data = data;
			this->_children.push_back(to_add);
		}
	};
}

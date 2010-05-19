/*******************************************************************************
 *	list.h
 *	Librería de lista simplemente enladada, con punteros a inicio y final
 *	Implementación de lista: Fiona González Lisella (Padrón 91454)
 *	Implementación de iteradores: Federico Churca Torrusio (Padrón 91352)
 *	Documentación: Federico Churca Torrusio (Padrón 91352)
*******************************************************************************/
#ifndef __LIST_H__
#define __LIST_H__
#include <cstdlib>

#include <stdexcept>
//**********************************************************
// namespace custom
//	Contiene clases diseñadas para reemplazar el uso de clases STL, compartiendo
//	los mismos nombres de procedimientos y el mismo comportamiento externo
namespace custom{
//**************************************
// custom::list
//	Lista simplemente enlazada con punteros a primer y último elemento
//	Clases propias:
//		node		//	Nodo de almacenamiento
//		iterator	//	Iterador progresivo
//	Miembros:
//		first		//	Puntero a primer nodo almacenado
//		last		//	Puntero a último nodo almacenado
//		Size		//	Cantidad de nodos
//	Métodos:
//		Constructor por defecto
//		Destructor
//		Leer tamaño
//		Borrar todo el contenido
//		Agregar al final de la lista
//		Remover desde el principio de la lista
//		Iterador hacia el principio de la lista
//		Iterador hacia el final de la lista
//		Insertar un dato en la posición dada por un iterador
	template <class T>
	class list{
	public:
		class iterator;	//	Forward declaration
	protected:
		class node;		//	Forward declaration
	// Cantidad de elementos guardados en el contenedor
		unsigned long Size;
	// Punteros a nodo
		node
		// Puntero hacia el primer elemento. NULL si la lista es vacía.
			* first,
		// Puntero hacia el último elemento. NULL si la lista es vacía.
			* last;
	//**************************************
	// custom::list::node
	//	Nodo de almacenamiento de una lista simplemente enlazada
	//	Miembros:
	//		next		//	Puntero a nodo siguiente
	//		data		//	Datos almacenados
	//	Métodos:
	//		Constructor por defecto
	//		Constructor por inicialización de datos
	//		Constructor copiador
		class node{
		protected:
		// Puntero al nodo siguiente en la lista. NULL si último elemento.
			node * next;
		// Datos almacenados en el nodo
			T data;
		public:
		//******************
		// Constructor por defecto
		//	Precondiciones:
		//		(ninguna)
		//	Postcondiciones:
		//		* El nodo se marca como último en una lista. Ésto se hace para
		//	que, si se usa, que haga el menor daño posible; es altamente
		//	recomendado inicializar manualmente el nodo y no dejarlo en este
		//	estado.	
			node(){
				this->next = NULL;
			}
		//******************
		// Constructor por inicialización de datos
		//	Precondiciones:
		//		(ninguna)
		//	Postcondiciones:
		//		* El nodo se inicializa con los datos dados, apuntando al nodo
		//			siguiente dado
			node(const T & data, node * next){
				this->data = data;
				this->next = next;
			}
		//******************
		// Constructor copiador
		//	Precondiciones:
		//		(ninguna)
		//	Postcondiciones:
		//		* El nodo es una copia del nodo dado
			node(const node & other){
				this->data = other.data;
				this->next = other.next;
			}
		// Permitir a list acceder a los miembros protegidos de node
		friend class list;
		};
	public:
	//**************************************
	// custom::list::iterator
	//	Iterador progresivo para una lista simplemente enlazada
	//	Miembros:
	//		parent		//	Puntero a objeto padre
	//		pos			//	Puntero a nodo referido
	//		at_end		//	Si está al final de la lista o no
	//		initialized	//	Si el iterador está inicializado o no
	//	Métodos:
	//		Constructor por defecto
	//		Constructor copiador
	
		class iterator{
			list * parent;
			node * pos;
			bool at_end;
			bool initialized;
		public:
		//******************
		// Constructor por defecto
		//	Precondiciones:
		//		(ninguna)
		//	Postcondiciones:
		//		* Marca al nodo como no inicializado. Ésto se hace para que no
		//	se pueda usar el nodo si no se especificó donde apunta.
			iterator(){
				this->initialized = false;
			}
		//******************
		// Constructor copiador
		//	Precondiciones:
		//		(ninguna)
		//	Postcondiciones:
		//		* El iterador es una copia del iterador dado
			iterator(const iterator & newit){
				this->parent = newit.parent;
				this->pos = newit.pos;
				this->at_end = newit.at_end;
				this->initialized = newit.initialized;
			}
			T & operator*();
			T * operator->();
			bool operator!=(const iterator & newit);
			bool operator==(const iterator & newit);
			iterator & operator++(){
				(*this)++;
				return *this;
			}
			iterator & operator++(int){
				if (this->initialized){
					if (this->at_end){
						throw std::runtime_error("Iterator at end");
					}else{
						this->pos = this->pos->next;
						if (this->pos == this->parent->last){
							this->at_end = true;
						}
					}
				}else{
					throw std::runtime_error("Iterator not initialized");
				}
				return *this;
			}
		friend class list;
		};
		list();
		~list();
		unsigned long size() const;
		void clear();
		void push_back(const T & data);
		T pop_front();
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
		void insert(const iterator & it, const T & data){
			if (!it.initialized){
				throw std::runtime_error("Iterator not initialized");
			}else if (it.parent != this){
				throw std::runtime_error("Wrong iterator parent");
			}else if (it.at_end || ! this->last){
				push_back(data);
			}else if (it.pos == this->first){
				this->Size++;
				node * to_add = new node(data, this->first);
				this->first = to_add;
				if (! this->last){
					this->last = to_add;
				}
			}else{
				this->Size++;
				node * to_add = new node(*it.pos);
				it.pos->next = to_add;
				it.pos->data = data;
			}
		}
	};
};
#include "list.cpp"
#endif	//	__LIST_H__

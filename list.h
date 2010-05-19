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
//		Iterador al principio de la lista
//		Iterador al final de la lista
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
	//		Operador de indirección
	//		Operador de miembro por indirección
	//		Operador de desigualdad
	//		Operador de igualdad
	//		Operador de preincremento
	//		Operador de postincremento
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
		//******************
		// Operador de indirección
		//	Precondiciones:
		//		* El iterador debe haber sido inicializado
		//	Postcondiciones:
		//		* Devuelve una referencia al contenido de la lista
		//	correspondiente al iterador
			T & operator*(){
				if(this->initialized){
					return pos->data;
				}else{
					throw std::runtime_error("Iterator not initialized");
				}
			}
		//******************
		// Operador de miembro por indirección
		//	Precondiciones:
		//		* El iterador debe haber sido inicializado
		//	Postcondiciones:
		//		* Devuelve un puntero al contenido de la lista correspondiente
		//	al iterador, para usar algún miembro suyo
			T * operator->(){
				if(this->initialized){
					return &(pos->data);
				}else{
					throw std::runtime_error("Iterator not initialized");
				}
			}
		//******************
		// Operador de desigualdad
		//	Precondiciones:
		//		* Los iteradores debe haber sido inicializados
		//		* Los iteradores deben pertenecer al mismo contenedor
		//	Postcondiciones:
		//		* Devuelve si ambos iteradores no apuntan al mismo elemento
			bool operator!=(const iterator & newit){
				return ! ((*this) == newit);
			}
		//******************
		// Operador igualdad
		//	Precondiciones:
		//		* Los iteradores debe haber sido inicializados
		//		* Los iteradores deben pertenecer al mismo contenedor
		//	Postcondiciones:
		//		* Devuelve si ambos iteradores apuntan al mismo elemento
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
		//******************
		// Operador de preincremento
		//	Precondiciones:
		//		* El iterador debe haber sido inicializado
		//		* El iterador no debe estar al final de la lista
		//	Postcondiciones:
		//		* El iterador avanza al próximo nodo
		//		* Retorna una referencia al iterador, que ahora apunta al
		//	próximo nodo
			iterator & operator++(){
				(*this)++;
				return *this;
			}
		//******************
		// Operador de postincremento
		//	Precondiciones:
		//		* El iterador debe haber sido inicializado
		//		* El iterador no debe estar al final de la lista
		//	Postcondiciones:
		//		* El iterador avanza al próximo nodo
		//		* Retorna una referencia al iterador, que ahora apunta al
		//	próximo nodo
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
	//******************
	// Constructor por defecto
	//	Precondiciones:
	//		(ninguna)
	//	Postcondiciones:
	//		* La lista fue creada vacía
		list(){
			this->first = this->last = NULL;
			this->Size = 0;
		}
	//******************
	// Destructor
	//	Precondiciones:
	//		(ninguna)
	//	Postcondiciones:
	//		* La lista está vacía
		~list(){
			this->clear();
		};
	//******************
	// Leer tamaño
	//	Precondiciones:
	//		(ninguna)
	//	Postcondiciones:
	//		* Devuelve la cantidad de elementos en la lista
		unsigned long size() const{
			return this->Size;
		};
	//******************
	// Borrar todo el contenido
	//	Precondiciones:
	//		(ninguna)
	//	Postcondiciones:
	//		* Quita todos los elementos de la lista
	//		* Establece el tamaño en cero
		void clear(){
			while(this->first){
				this->pop_front();
			}
		}
	//******************
	// Agregar al final de la lista
	//	Precondiciones:
	//		(ninguna)
	//	Postcondiciones:
	//		* Agrega un elemento al final de la lista
	//		* Incrementa el tamaño en un elemento más
		void push_back(const T & data){
			node * to_add = new node(data, NULL);
			if (this->last){
				this->last->next = to_add;
			}else{
				this->first = to_add;
			}
			this->last = to_add;
			this->Size++;
		};
	//******************
	// Remover desde el frente de la lista
	//	Precondiciones:
	//		* La lista debe tener un elemento o más
	//	Postcondiciones:
	//		* Quita un elemento del inicio de la lista
	//		* Decrementa el tamaño en un elemento menos
		T pop_front(){
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
	//******************
	// Iterador al principio de la lista
	//	Precondiciones:
	//		(ninguna)
	//	Postcondiciones:
	//		* Devuelve un iterador que apunta al principio de la lista
	//		* Si es una lista vacía, el iterador también apunta al final
		iterator begin(){
			iterator ret;
			ret.parent = this;
			ret.at_end = !(this->first);
			ret.initialized = true;
			ret.pos = this->first;
			return ret;
		}
	//******************
	// Iterador al final de la lista
	//	Precondiciones:
	//		(ninguna)
	//	Postcondiciones:
	//		* Devuelve un iterador que apunta al final de la lista
		iterator end(){
			iterator ret;
			ret.parent = this;
			ret.at_end = true;
			ret.initialized = true;
			ret.pos = NULL;
			return ret;
		}
	//******************
	// Insertar en la posición dada por un iterador
	//	Precondiciones:
	//		* El iterador debe haber sido inicializado
	//		* El iterador debe pertenecer a el contenedor en cuestión
	//	Postcondiciones:
	//		* Agrega un nodo en la posición dada
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
#endif	//	__LIST_H__

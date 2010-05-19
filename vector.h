/*******************************************************************************
 *	list.h
 *	Librería de vector dinámico
 *	Implementación de lista: Fiona González Lisella (Padrón 91454)
 *	Implementación de iteradores: Federico Churca Torrusio (Padrón 91352)
 *	Documentación: Federico Churca Torrusio (Padrón 91352)
*******************************************************************************/
#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <cstdlib>
#include <stdexcept>

//**********************************************************
// namespace custom
//	Contiene clases diseñadas para reemplazar el uso de clases STL, compartiendo
//	los mismos nombres de procedimientos y el mismo comportamiento externo
namespace custom{
//**************************************
// custom::vector
//	Vector de arreglo dinámico
//	Clases propias:
//		iterator	//	Iterador progresivo
//	Miembros:
//		Size		//	Cantidad de elementos almacenados
//		capacity	//	Cantidad de elementos que se pueden almacenar
//		contents	//	Arreglo dinámico con los contenidos del vector
//	Métodos:
//		Constructor por defecto
//		Destructor
//		Leer tamaño
//		Acceso por índice
//		Borrar todo el contenido
//		Cambiar capacidad
//		Agregar al final del vector
//		Remover desde el final del vector
//		Iterador al principio del vector
//		Iterador al final del vector
//		Insertar un dato en la posición dada por un iterador
	template <class T> class vector{
		unsigned long
		// Cantidad de elementos ya almacenados en el vector
			Size,
		// Cantidad de elementos que se pueden almacenar. Si se quiere almacenar
		//	más que esta cantidad de elementos, las funciones de inserción
		//	aumentarán la capacidad pidiendo más memoria (ver list::push_back())
			capacity;
	// Arreglo de elementos de tipo T residente en memoria heap
		T * contents;
	public:
	//**************************************
	// custom::vector::iterator
	//	Iterador progresivo para una lista simplemente enlazada
	//	Miembros:
	//		parent		//	Puntero a objeto padre
	//		pos			//	Índice a nodo referido
	//		at_end		//	Si el iterador está al final de la lista o no
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
		// Puntero a contenedor padre (donde reside el nodo referido)
			vector * parent;
		// Índice al nodo referido
			unsigned long pos;
		// Si el iterador está al final de la lista o no
			bool at_end;
		// Si el iterador fue inicializado o no
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
				this->parent = NULL;
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
				this->at_end = newit.pos;
				this->initialized = newit.initialized;
			}
		//******************
		// Operador de indirección
		//	Precondiciones:
		//		* El iterador debe haber sido inicializado
		//	Postcondiciones:
		//		* Devuelve una referencia al contenido del vector
		//	correspondiente al iterador
			T & operator*(){
				if (this->initialized){
					return parent->at(this->pos);
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
					return &(this->parent->at(pos));
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
			void operator++(){
				(*this)++;
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
			void operator++(int){
				if (this->initialized){
					if (this->at_end){
						throw std::runtime_error("Iterator at end");
					}else{
						this->pos++;
						this->at_end = (this->pos == this->parent->size());
					}
				}else{
					throw std::runtime_error("Iterator not initialized");
				}
			}
		friend class vector;
		};
	//******************
	// Constructor por defecto
	//	Precondiciones:
	//		(ninguna)
	//	Postcondiciones:
	//		* El vector fue creado vacío, con capacidad para un elemento
		vector(){
			this->capacity = 1;
			this->contents = new T[this->capacity];
			this->Size = 0;
		}
	//******************
	// Destructor
	//	Precondiciones:
	//		(ninguna)
	//	Postcondiciones:
	//		* Se libera la memoria usada por el vector. Se apunta el contenido
	//	del vector a NULL para que todo acceso falle de la forma menos
	//	destructiva posible
		~vector(){
			delete[] this->contents;
			this->contents = NULL;
		}
	//******************
	// Acceso por índice
	//	Precondiciones:
	//		* El índice debe apuntar a un elemento existente del vector
	//	Postcondiciones:
	//		* Devuelve una referencia al pos-ésimo elemento del vector
		T & at(unsigned long pos){
			if (pos < this->Size){
				return this->contents[pos];
			}else{
				throw std::runtime_error("Outside bonds");
			}
		}
	//******************
	// Leer tamaño
	//	Precondiciones:
	//		(ninguna)
	//	Postcondiciones:
	//		* Devuelve la cantidad de elementos almacenados en el vector
		unsigned long size() const{
			return this->Size;
		}
	//******************
	// Borrar todo el contenido
	//	Precondiciones:
	//		(ninguna)
	//	Postcondiciones:
	//		* Establece el tamaño en cero
		void clear(){
			this->Size = 0;
		}
	//******************
	// Cambiar capacidad
	//	Precondiciones:
	//		* La capacidad nueva debe ser mayor a la antigua
	//	Postcondiciones:
	//		* Reemplaza el arreglo almacenado por uno de mayor tamaño
	//		* Copia los contenidos del viejo al nuevo
	//		* Libera la memoria usada por el arreglo viejo
		void change_capacity(unsigned long capacity){
			if (this->capacity > capacity){
				throw std::runtime_error("New capacity smaller than old");
			}else{
				T * contents = new T [capacity];
				for(unsigned long i = 0; i < this->Size; i++){
					contents[i] = this->contents[i];
				}
				delete[] this->contents;
				this->contents = contents;
				this->capacity = capacity;
			}
		}
	//******************
	// Agregar al final del vector
	//	Precondiciones:
	//		(ninguna)
	//	Postcondiciones:
	//		* Agrega un elemento al final del vector
	//		* Incrementa el tamaño en un elemento más
	//		* Si no había espacio libre, duplica la capacidad. Se hace por
	//	cuestiones estadísticas; "si ya almacenamos una determinada cantidad n
	//	de elementos, es posible que querramos almacenar n elementos más".
		void push_back(const T & data){
			if (this ->Size == this->capacity){
				this->change_capacity(this->capacity * 2);
			}
			this->contents[this->Size] = data;
			this->Size++;
		}
	//******************
	// Remover desde el frente del vector
	//	Precondiciones:
	//		* El vector debe tener un elemento o más
	//	Postcondiciones:
	//		* Quita un elemento del final del vector
	//		* Decrementa el tamaño en un elemento menos
		T pop_back(){
			if (this->Size){
				return this->contents[--(this->Size)];
			}else{
				throw std::runtime_error("Nothing to pop");
			}
		}
	//******************
	// Iterador al principio del vector
	//	Precondiciones:
	//		(ninguna)
	//	Postcondiciones:
	//		* Devuelve un iterador que apunta al principio del vector
	//		* Si es un vector vacío, el iterador también apunta al final
		iterator begin(){
			iterator ret;
			ret.parent = this;
			ret.at_end = !this->Size;
			ret.initialized = true;
			ret.pos = 0;
			return ret;
		}
	//******************
	// Iterador al final del vector
	//	Precondiciones:
	//		(ninguna)
	//	Postcondiciones:
	//		* Devuelve un iterador que apunta al final del vector
		iterator end(){
			iterator ret;
			ret.parent = this;
			ret.at_end = true;
			ret.initialized = true;
			ret.pos = this->Size;
			return ret;
		}
	//******************
	// Insertar en la posición dada por un iterador
	//	Precondiciones:
	//		* El iterador debe haber sido inicializado
	//		* El iterador debe pertenecer a el contenedor en cuestión
	//		* El iterador debe apuntar, como mucho, al elemento siguiente al
	//	último elemento del vector
	//	Postcondiciones:
	//		* Agrega un nodo en la posición dada
		void insert(const iterator & it, const T & data){
			if (!it.initialized){
				throw std::runtime_error("Iterator not initialized");
			}else if (it.parent != this){
				throw std::runtime_error("Wrong iterator parent");
			}else if (it.pos > this->Size){
				throw std::runtime_error("Outside bonds");
			}else{
				this->push_back(data);
				for(unsigned long i = this->Size - 1; i > it.pos; i--){
					T aux = this->at(i);
					this->at(i) = this->at(i-1);
					this->at(i-1) = aux;
				}
			}
		}
	};
}

#include "vector.cpp"

#endif	//	__VECTOR_H__

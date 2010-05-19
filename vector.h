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
			vector * parent;
			unsigned long pos;
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
		~vector()
		T & at(unsigned long pos);
		unsigned long size() const;
		void clear();
		void change_capacity(unsigned long capacity);
		void push_back(const T & data);
		T pop_back();;
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
		void insert(const iterator & it, const T & data);
	};
}

#include "vector.cpp"

#endif	//	__VECTOR_H__

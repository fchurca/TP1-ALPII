/*******************************************************************************
 *	FModel.h
 *	Clase nodo de sistema de archivos
 *	Implementación:               Federico Churca Torrusio (Padrón 91352)
*******************************************************************************/

#ifndef __FMODEL_H__
#define __FMODEL_H__

#include <sys/stat.h>

#include <string>
#include <cstdlib>

#include <ostream>

//**************************************
// humansize()
//	Translates a unsigned long size in bytes into STL string with binary powers
std::string humansize(unsigned long size);

//**************************************
// FSMode
//	Modelo de nodo de sistema de archivos
//	Miembros:
//		name		//	Nombre del nodo
//		path		//	Ubicación del nodo
//		fullname	//	Nombre completo del nodo
//		isdir		//	Si el nodo es o no un directorio
//		size		//	Cantidad de subelementos del directorio, o tamaño en
//					//		bytes del archivo
//		mtime		//	Fecha Unix de última modificación
//	Métodos:
//		Constructor por defecto
//		Construtcores por filename
//		Carga por filename
//		Volcado de contenidos
class FModel{
public:
//**************************************
// Methods

//******************
// FModel()
//	Zeroing default constructor
	FModel();

//******************
// FModel(const char * path)
//	Load node information
//	May throw runtime_error if path is unreachable
	FModel(const char * path);

//******************
// FModel(const std::string & path)
//	Wrap to cstring version
//	May throw runtime_error if path is unreachable
	FModel(const std::string & path);

//******************
// load(const char *)
//	Load node information
//	May throw runtime_error if path is unreachable
	void load(const char * path);

//******************
// load(const std::string &)
//	Wrap to cstring version
//	May throw runtime_error if path is unreachable
	void load(const std::string & path);

//******************
// dump(std::ostream&)
//	Dump contents to std::ostream out
	void dump(std::ostream & out) const;

//**************************
// Getters

	const std::string &getname() const;
	const std::string &getpath() const;
	std::string getfullname() const;
	bool getisDirectory() const;
	time_t getmtime() const;
	std::string getCmtime() const;
	unsigned long getsize() const;

//**************************************
// Members
protected:
//******************
// Filename
	std::string name;

//******************
// File location
	std::string path;

//******************
// Full filename
	std::string fullname;
	
//******************
// Node type
//	true if directory, false if file or device
	bool isdir;

//******************
// Subelements if directory, or size of the node in bytes if file
	unsigned long size;

//******************
// Unix time of last modification
	time_t mtime;

//**************************************
// Friends

//******************
// class FSModel
//	Will need access to protected members to be able to load them more quickly
//	(albeit less elegantly)
friend class FSModel;
};

#endif	// __FModel_H__

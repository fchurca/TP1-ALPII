#ifndef __FSMODEL_H__
#define __FSMODEL_H__

#if defined(FSMODEL_LIST) && defined(FSMODEL_VECTOR)
	#error "Define one and only one of FSMODEL_LIST or FSMODEL_VECTOR!"
#else

#include "fsnode.h"

#include <ostream>

#if ! (defined(FSMODEL_LIST) || defined(FSMODEL_VECTOR))
	#error "Define one and only one of FSMODEL_LIST or FSMODEL_VECTOR!"
#else

#if defined(FSMODEL_STD)
	#if defined(FSMODEL_VECTOR)
		#include <vector>
		typedef std::vector<FSNode> container;
	#elif defined(FSMODEL_LIST)
		#include <list>
		typedef std::list<FSNode> container;
	#endif
#else
	#if defined(FSMODEL_VECTOR)
		#include "vector.h"
		typedef custom::vector<FSNode> container;
	#elif defined(FSMODEL_LIST)
		#include "list.h"
		typedef custom::list<FSNode> container;
	#endif
#endif
class FSModel{
public:
//**************************************
// Methods

//******************
// FSModel()
//	Empty default constructor
	FSModel();

//******************
// FSModel(const std::string & path)
//	Set path and load tree
//	May throw runtime_error if path is unreachable
	FSModel(const std::string & path);

//******************
// load(const std::string &)
//	Load tree
//	May throw runtime_error if path is unreachable
//	Returns amount of nodes loaded
	unsigned long load(const std::string & path);

//******************
// clear()
//	Clear tree and path
	void clear();

//******************
// dump(std::ostream &)
//	Dump contents, unfiltered, to std::ostream out
	void dump(std::ostream & out);

//******************
// search(std::ostream &, const std::string &)
//	Dump contents to std::ostream out
//		Filters local name by expression
//		Filters size by max and min
//	With one size parameter, will only evaluate maxsize
//	With no size parameters, will not evaluate size
	void search(
		std::ostream & out, const std::string & expression,
		unsigned long maxsize = -1, unsigned long minsize = 0
	);

//**************************
// Getters
	const container & getcontents() const;
	const std::string & getpath() const;
	unsigned long getsize() const;

protected:
	container contents;
	std::string path;
};

#endif	// ! (defined(FSMODEL_LIST) || defined(FSMODEL_VECTOR))

#endif	// defined(FSMODEL_LIST) && defined(FSMODEL_VECTOR)

#endif	// __FSMODEL_H__

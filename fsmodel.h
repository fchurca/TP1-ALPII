#if defined(FSMODEL_LIST) && defined(FSMODEL_VECTOR)
#error "Define one and only one of FSMODEL_LIST or FSMODEL_VECTOR!"
#endif

#ifndef __FSMODEL_H__
#define __FSMODEL_H__

#include "fsnode.h"

#include <ostream>

#if defined(FSMODEL_VECTOR)
	#include <vector>
	typedef std::vector<FSNode> container;
#elif defined(FSMODEL_LIST)
	#include <list>
	typedef std::list<FSNode> container;
#endif
#if defined(FSMODEL_LIST) || defined(FSMODEL_VECTOR)

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
	size_t load(const std::string & path);

//******************
// dump(std::ostream&)
//	Dump contents. unfiltered, to std::ostream out
	void dump(std::ostream & out);

protected:
	container contents;
	std::string path;
};
#else
#error "Define one and only one of FSMODEL_LIST or FSMODEL_VECTOR!"
#endif

#endif

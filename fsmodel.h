#if defined(FSMODEL_LIST) && defined(FSMODEL_VECTOR)
#error "Define one and only one of FSMODEL_LIST or FSMODEL_VECTOR!"
#endif

#ifndef __FSMODEL_H__
#define __FSMODEL_H__

#include "fsnode.h"

#if defined(FSMODEL_VECTOR)
	#include <vector>
	typedef std::vector<FSNode> container;
#elif defined(FSMODEL_LIST)
	#include <list>
	typedef std::list<FSNode> container;
#endif
#if defined(FSMODEL_LIST) || defined(FSMODEL_VECTOR)

class FSModel{
	container contents;
// Rest of header 

};
#else
#error "Define one and only one of FSMODEL_LIST or FSMODEL_VECTOR!"
#endif

#endif

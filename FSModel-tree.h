#ifndef __FSMODEL_TREE_H__
#define __FSMODEL_TREE_H__

#include "expr.h"
#include "tree.h"
#include "FModel.h"

#include <cstdlib>
#include <dirent.h>

#include <iostream>
#include <stdexcept>

class FSModel{
	custom::tree<FModel> contents;
	unsigned _load(const std::string & path, custom::tree<FModel> & here);
	unsigned _dump(std::ostream & out, custom::tree<FModel> & here);
	unsigned _search(
		std::ostream & out, const std::string & expression,
		unsigned long maxsize, unsigned long minsize,
		custom::tree<FModel> & here
	);
public:
	void clear();
	unsigned getsize();
	std::string getpath();
	unsigned load(const std::string & path);
	unsigned dump(std::ostream & out);
	void search(
		std::ostream & out, const std::string & expression,
		unsigned long maxsize = -1, unsigned long minsize = 0
	);
};

#endif	// __FSMODEL-TREE_H__

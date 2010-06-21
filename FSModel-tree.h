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
	unsigned _load(const std::string & path, custom::tree<FModel> & here){
		unsigned ret = 1;
		here.data().load(path);
	// Check dir
		if (DIR * dirp = opendir(path.c_str())){
			if (path[path.length() - 1] != '/'){
				here.data().fullname.push_back('/');
			}
			here.data().size = 0;
			struct dirent *dp = NULL;
			FModel curnode;
			curnode.path = here.data().fullname;
			while (dp = readdir(dirp)){
				try{
					curnode.name = dp->d_name;
					curnode.load(curnode.path + curnode.name);
				// Ignore self, parent
					if (
						(curnode.getname() != ".") &&
						(curnode.getname() != "..") &&
						(curnode.getname() != "./") &&
						(curnode.getname() != "../")
					){
						custom::list<custom::tree<FModel> >::iterator inpoint = here.children().begin();
						here.children().insert(inpoint, custom::tree<FModel>());
						inpoint = here.children().begin();
						here.data().size += this->_load(curnode.fullname, *inpoint);
						inpoint->data().name = curnode.name;
					}
				}catch (std::runtime_error e){
					std::cerr << e.what() << std::endl;
				}
			}
			ret += here.data().size;
			closedir(dirp);
		}
		return ret;
	}
	unsigned _dump(std::ostream & out, custom::tree<FModel> & here){
		unsigned ret = 0;
		custom::list<custom::tree<FModel> >::iterator it = here.children().begin();
		for(
			custom::list<custom::tree<FModel> >::iterator end = here.children().end();
			it != end;
			it++
		){
			it->data().dump(out);
			ret++;
			ret += this->_dump(out, *it);
		}
		return ret;
	}
	unsigned _search(
		std::ostream & out, const std::string & expression,
		unsigned long maxsize, unsigned long minsize,
		custom::tree<FModel> & here
	){
		unsigned ret = 0;
		custom::list<custom::tree<FModel> >::iterator it = here.children().begin();
		for(
			custom::list<custom::tree<FModel> >::iterator end = here.children().end();
			it != end;
			it++
		){
			if (
			// Should match expression
				MatchesExpression(expression, it->data().getname()) && (
				// Match all dirs
					it->data().getisDirectory() || (
					// Files should have a size between, and including, min and max
						(it->data().getsize() <= maxsize) &&
						(it->data().getsize() >= minsize)
					)
				)
			){
				it->data().dump(out);
				ret++;
			}
			ret += this->_search(out, expression, maxsize, minsize, *it);
		}
		return ret;
	}
public:
	void clear(){
		this->contents.clear();
	}
	unsigned getsize(){
		return this->contents.data().getsize();
	}
	std::string getpath(){
		return this->contents.data().getfullname();
	}
	unsigned load(const std::string & path){
		return this->_load(path, this->contents);
	}
	unsigned dump(std::ostream & out){
		out
			<< "Contents of " << this->contents.data().path << std::endl
			<< "Type Size\tDate                     Name" << std::endl;
		unsigned ret = this->_dump(out, this->contents);
		out << "Total: " << ret << " elements" << std::endl;
		return ret;
	}
	void search(
		std::ostream & out, const std::string & expression,
		unsigned long maxsize = -1, unsigned long minsize = 0
	){
		out
			<< "Contents of " << this->contents.data().path << std::endl
			<< "Total: " << this->contents.data().getsize() << " elements" << std::endl
			<< "Type Size\tDate                     Name" << std::endl;
		unsigned long found = this->_search(out, expression, maxsize, minsize, this->contents);
		out <<
			"Searching for \"" << expression << "\" in \"" << this->contents.data().fullname
			<< "\" turned out  " << found << " results" << std::endl;
	}
};
#endif	// __FSMODEL-TREE_H__

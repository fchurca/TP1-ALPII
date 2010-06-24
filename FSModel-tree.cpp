#include "expr.h"
#include "tree.h"
#include "FModel.h"

#include "FSModel-tree.h"

#include <cstdlib>
#include <dirent.h>

#include <iostream>
#include <stdexcept>

unsigned FSModel::_load(const std::string & path, custom::tree<FModel> & here){
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
unsigned FSModel::_dump(std::ostream & out, custom::tree<FModel> & here){
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
unsigned FSModel::_search(
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
void FSModel::clear(){
	this->contents.clear();
}
unsigned FSModel::getsize(){
	return this->contents.data().getsize();
}
std::string FSModel::getpath(){
	return this->contents.data().getfullname();
}
unsigned FSModel::load(const std::string & path){
	if(!FModel(path).getisDirectory()){
		throw std::runtime_error(path + " not a valid dir");
	}
	this->contents.data().name = path;
	return this->_load(path, this->contents);
}
unsigned FSModel::dump(std::ostream & out){
	out
		<< "Contents of " << this->contents.data().name << std::endl
		<< "Type Size\tDate                     Name" << std::endl;
	unsigned ret = this->_dump(out, this->contents);
	out << "Total: " << ret << " elements" << std::endl;
	return ret;
}
void FSModel::search(
	std::ostream & out, const std::string & expression,
	unsigned long maxsize, unsigned long minsize
){
	out
		<< "Contents of " << this->contents.data().name << std::endl
		<< "Total: " << this->contents.data().getsize() << " elements" << std::endl
		<< "Type Size\tDate                     Name" << std::endl;
	unsigned long found = this->_search(out, expression, maxsize, minsize, this->contents);
	out <<
		"Searching for \"" << expression << "\" in \"" << this->contents.data().name
		<< "\" turned out  " << found << " results" << std::endl;
}

#ifndef FSMODEL_TREE

using namespace std;
int main(int argc, char **argv){
	FSModel arbol;
	arbol.load(argv[1]);
	arbol.dump(cout);
	arbol.search(cout, argv[2]);
	return EXIT_SUCCESS;
}

#endif

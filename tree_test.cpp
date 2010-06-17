#include "tree.h"
#include "FModel.h"

#include <cstdlib>
#include <dirent.h>

#include <iostream>
#include <stdexcept>

using namespace custom;
using namespace std;
class FSModel{
	tree<FModel> contents;
public:
	unsigned _load(const std::string & path, tree<FModel> & here){
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
						list<tree<FModel> >::iterator inpoint = here.children().begin();
						here.children().insert(inpoint, tree<FModel>());
						inpoint = here.children().begin();
						here.data().size += this->_load(curnode.fullname, *inpoint);
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
	unsigned load(const std::string & path){
		return this->_load(path, this->contents);
	}
	unsigned _dump(std::ostream & out,  tree<FModel> & here){list<tree<FModel> >::iterator inpoint = here.children().begin();
		unsigned ret = 0;
		list<tree<FModel> >::iterator it = here.children().begin();
		for(
			list<tree<FModel> >::iterator end = here.children().end();
			it != end;
			it++
		){
			it->data().dump(out);
			ret++;
			ret += this->_dump(out, *it);
		}
		return ret;
	}
	unsigned dump(std::ostream & out){
		out
			<< "Contents of " << this->contents.data().path << std::endl
			<< "Type Size\tDate                     Name" << std::endl;
		unsigned ret = this->_dump(out, this->contents);
		out << "Total: " << ret << " elements" << std::endl;
		return ret;
	}
};

int main(int argc, char **argv){
	FSModel arbol;
	arbol.load(argv[1]);
	arbol.dump(cout);
	return EXIT_SUCCESS;
}


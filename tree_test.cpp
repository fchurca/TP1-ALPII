#include "tree.h"
#include "FModel.h"

#include <cstdlib>
#include <dirent.h>

#include <iostream>
#include <stdexcept>

using namespace custom;
using namespace std;
class FSModel : public tree<FModel>{
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
			while (dp = readdir(dirp)){
				try{
					FModel curnode;
					curnode.path = here.data().fullname;
					curnode.name = dp->d_name;
					curnode.load(curnode.path + curnode.name);
				// Ignore self, parent
					if (
						(curnode.getname() != ".") &&
						(curnode.getname() != "..") &&
						(curnode.getname() != "./") &&
						(curnode.getname() != "../")
					){
						tree<FModel> empty;
				// Ordered insertion
/*						list<tree<FModel> >::iterator inpoint = here.children().begin();
						for(
							list<tree<FModel> >::iterator end = here.children().end();
							inpoint != end;
							inpoint++
						){
							if (curnode.fullname < inpoint->data().fullname){
								break;
							}
						}
*/
						list<tree<FModel> >::iterator inpoint = here.children().begin();
						here.children().insert(inpoint, empty);
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
		this->_load(path, this->contents);
		return 0;
	}
	unsigned dump(std::ostream & out, bool verbose = true){
		if (verbose){
			out
				<< "Contents of " << this->data().path << std::endl
				<< "Type Size\tDate                     Name" << std::endl;
		}
		unsigned ret = 1;
		this->data().dump(out);
		list<tree<FModel> >::iterator
			it = this->contents.children().begin(),
			end = this->contents.children().end();
		while(it != end){
			it->data().dump(out);
			ret++;
			it++;
		}
		if (verbose){
			out << "Total: " << this->contents.data().size << " elements" << std::endl;
		}
		return ret;
	}
};

int main(int argc, char **argv){
	FSModel arbol;
	arbol.load(".");
	arbol.dump(cout);
	cout << "WARGBL"<< endl;
	return EXIT_SUCCESS;
}


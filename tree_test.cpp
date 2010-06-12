#include "tree.h"
#include "FModel.h"

#include <cstdlib>
#include <dirent.h>

#include <iostream>

using namespace custom;
using namespace std;
class FSModel : public tree<FModel>{
public:
	unsigned load(const std::string & path){
	// Will return amount of sub(all)elements
		unsigned long localsize = 0;
		FSModel curnode;

	/* Set node path and add slash if missing. If on Microsoft Windows, the slash
	*	is mandatory too, since we are using a POSIX environment in the first place
	*	(Interix / GNUWin / Cygwin / MinGW)
	*/
		curnode.data().path = path;
		if (path[path.length() - 1] != '/'){
			curnode.data().path.push_back('/');
		}
	// Check valid dir
		if (DIR * dirp = opendir(path.c_str())){
			struct dirent *dp = NULL;
			while (dp = readdir(dirp)){
				try{
				// Load stats, name
					curnode.data().name = dp->d_name;
					curnode.data().load(curnode.data().path + curnode.data().name);
				// Ignore self, parent
					if (
						(curnode.data().getname() != ".") &&
						(curnode.data().getname() != "..") &&
						(curnode.data().getname() != "./") &&
						(curnode.data().getname() != "../")
					){
					// If node is a dir, load children
						if (curnode.data().getisDirectory()){
							localsize += curnode.data().size = this->load(curnode.data().fullname);
						}
					// Load node
				// Ordered insertion
						list<tree<FModel> >::iterator inpoint = this->children().begin();
						for(
							list<tree<FModel> >::iterator end = this->children().end();
							inpoint != end;
							inpoint++
						){
							if (curnode.data().fullname < inpoint->data().fullname){
								break;
							}
						}
						this->children().insert(inpoint, curnode);
						localsize++;
					}
				}catch (std::runtime_error e){
					std::cerr << e.what() << std::endl;
				}
			}
			closedir(dirp);
		}else{
			throw std::runtime_error(std::string(path) + " not a valid dir");
		}
		return localsize;
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
			it = this->children().begin(),
			end = this->children().end();
		while(it != end){
			it->data().dump(out);
			ret++;
			it++;
		}
		if (verbose){
			out << "Total: " << ret << " elements" << std::endl;
		}
		return ret;
	}
};

int main(int argc, char **argv){
	FSModel arbol;
	arbol.load(".");
	arbol.dump(cout);
	return EXIT_SUCCESS;
}


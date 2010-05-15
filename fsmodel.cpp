#include "fsmodel.h"
#include "expr.h"

#include <dirent.h>
#include <cstring>

#include <stdexcept>

//**************************************
// FSModel methods

//******************
// FSModel()
//	Empty default constructor
FSModel::FSModel(){
	this->size = 0;
}

//******************
// FSModel(const std::string & path)
//	Set path and load tree
FSModel::FSModel(const std::string & path){
	this->size = 0;
	this->path = path;
	this->load(path);
}

//******************
// load(const std::string &)
//	Load tree
//	Returns amount of nodes loaded
size_t FSModel::load(const std::string & path){
// Will return sub(all)elements
	size_t localsize = 0;
	FSNode curnode;

	if (!path.length()){
		throw std::runtime_error("Empty dirname");
	}

/* Set node path and add slash if missing. If on Microsoft Windows, the slash
*	is mandatory too, since we are using a POSIX environment in the first
*	place (Interix / SUA / GNUWin / Xming / Cygwin / MinGW)
*/	
	curnode.path = path;
	if (path[path.length()-1] != '/'){
		curnode.path.push_back('/');
	}

	if (DIR * dirp = opendir(path.c_str())){
		struct dirent *dp;
		while (dp = readdir(dirp)){
		// Load stats, name
			curnode.name = dp->d_name;
			curnode.fullname = curnode.path + curnode.name;
			curnode.load(curnode.fullname);
		// Ignore self, parent
			if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")){
				localsize++;
				this->size++;
				if (curnode.isdir){
				// Load directory's children.
					// And its children's children.
						// And its children's children's children...
					localsize += curnode.size = this->load(curnode.fullname);
				}
				curnode.name = dp->d_name;
// Ordered insertion (move to container class?)
				container::iterator
					inpoint,
					begin = this->contents.begin(),
					end = this->contents.end();
				for(inpoint = this->contents.begin(); inpoint != end; inpoint++){
					if (curnode.compare(*inpoint) < 0){
						break;
					}
				}
				this->contents.insert(inpoint, curnode);
			}
		}
		closedir(dirp);
	}else{
		throw std::runtime_error(std::string(path) + " not a valid dir");
	}
	this->path = path;
	return localsize;
}

//******************
// dump(std::ostream&)
//	Dump contents, unfiltered, to std::ostream out
void FSModel::dump(std::ostream & out) const{
	out
		<< "Contents of " << this->path << std::endl
		<< "Total: " << this->size << " elements" << std::endl
		<< "Type Size\tDate                     Name" << std::endl;
	for (
		container::const_iterator
			iterator = this->contents.begin(),
			end = this->contents.end();
		iterator != end;
		iterator++
	){
		iterator->dump(out);
	}
}

//******************
// search(std::ostream &, const std::string &)
//	Dump contents to std::ostream out, filtering local name by expression
void FSModel::search(std::ostream & out, const std::string & expression) const{
	out
		<< "Contents of " << this->path << std::endl
		<< "Total: " << this->size << " elements" << std::endl
		<< "Type Size\tDate                     Name" << std::endl;
	size_t found = 0;
	for (
		container::const_iterator
			iterator = this->contents.begin(),
			end = this->contents.end();
		iterator != end;
		iterator++
	){
		if (MatchesExpression(expression, iterator->getname())){
			iterator->dump(out);
			found++;
		}
	}
	out << "Found: " << found << std::endl;
}

//**************************
// Getters
const container & FSModel::getcontents() const{
	return this->contents;
}
const std::string & FSModel::getpath() const{
	return this->path;
}
size_t FSModel::getsize() const{
	return this->size;
}

#ifdef FSMODEL_DEBUG

#include <iostream>

using namespace std;

int main(int argc, char **argv){
	int ret = EXIT_SUCCESS;
	if (argc > 1){
		try{
			FSModel mymodel;
			mymodel.load(argv[1]);
			mymodel.dump(cout);
		}catch(std::runtime_error e){
			cerr << e.what() << endl << "Aborting" << endl;
			ret = EXIT_FAILURE;
		}catch(std::exception e){
			cerr << e.what() << endl << "Aborting" << endl;
		}catch(...){
			cerr << "Unhandled exception" << endl << "Aborting" << endl;
			ret = EXIT_FAILURE;
		}
	}else{
		cout << "Usage:\t" << argv[0] << " <path>" << endl;
	}
	return ret;
}

#endif	// FSMODEL_DEBUG

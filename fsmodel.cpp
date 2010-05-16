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
}

//******************
// FSModel(const std::string & path)
//	Load tree
FSModel::FSModel(const std::string & path){
	this->load(path);
}

//******************
// load(const std::string &)
//	Load tree
//	Returns amount of nodes loaded
size_t FSModel::load(const std::string & path){
// Will return amount of sub(all)elements
	size_t localsize = 0;
	FSNode curnode;

/* Set node path and add slash if missing. If on Microsoft Windows, the slash
*	is mandatory too, since we are using a POSIX environment in the first place
*	(Interix / SUA / GNUWin / Xming / Cygwin / MinGW)
*/	
	curnode.path = path;
	if (path[path.length()-1] != '/'){
		curnode.path.push_back('/');
	}
// Check valid dir
	if (DIR * dirp = opendir(path.c_str())){
	// If model was already loaded, clear it
		if (this->path.length()){
			this->clear();
		}
		struct dirent *dp = NULL;
		while (dp = readdir(dirp)){
		// Load stats, name
			curnode.name = dp->d_name;
			curnode.load(curnode.path + curnode.name);
		// Ignore self, parent
			if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")){
				localsize++;
				if (curnode.isdir){
				// Load directory's children.
					// And its children's children.
						// And its children's children's children...
					localsize += curnode.size = this->load(curnode.fullname);
				}
				curnode.name = dp->d_name;
		// Ordered insertion
				container::iterator
					begin = this->contents.begin(),
					end = this->contents.end(),
					inpoint = begin;
				while(inpoint != end){
					if (curnode.compare(*inpoint) < 0){
						break;
					}
					inpoint++;
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
		<< "Total: " << this->getsize() << " elements" << std::endl
		<< "Type Size\tDate                     Name" << std::endl;
	for (
		container::const_iterator
			it = this->contents.begin(),
			end = this->contents.end();
		it != end;
		it++
	){
		it->dump(out);
	}
}

//******************
// clear()
//	Clear tree and path
void FSModel::clear(){
	this->path = "";
	this->contents.clear();
}

//******************
// search(std::ostream &, const std::string &)
//	Dump contents to std::ostream out
//		Filters local name by expression
//		Filters size by max and min
//	With one size parameter, will assume minsize = 0 and only evaluate maxsize
//	With no size parameters, will assume maxsize = -1 and not evaluate size
void FSModel::search(
	std::ostream & out, const std::string & expression,
/* maxsize is unsigned. Assigning -1 to it will pump it to the maximum possible
*	unsigned value
*/
	size_t maxsize = -1, size_t minsize = 0
) const{
	out
		<< "Contents of " << this->path << std::endl
		<< "Total: " << this->getsize() << " elements" << std::endl
		<< "Type Size\tDate                     Name" << std::endl;
	size_t found = 0;
	for (
		container::const_iterator
			it = this->contents.begin(),
			end = this->contents.end();
		it != end;
		it++
	){
		if (
		// Should match expression
			MatchesExpression(expression, it->getname()) && (
			// Match all dirs
				it->getisDirectory() || (
				// Files should have a size between, and including, min and max
					(it->getsize() <= maxsize) ||
					(it->getsize() >= minsize)
				)
			)
		){
			it->dump(out);
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
	return this->contents.size();
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

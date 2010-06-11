#include "FSModel.h"
#include "expr.h"

#include <dirent.h>
#include <cstring>

#include <iostream>

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
unsigned long FSModel::load(const std::string & path){
// Will return amount of sub(all)elements
	unsigned long localsize = 0;
	FModel curnode;

/* Set node path and add slash if missing. If on Microsoft Windows, the slash
*	is mandatory too, since we are using a POSIX environment in the first place
*	(Interix / GNUWin / Cygwin / MinGW)
*/	
	curnode.path = path;
	if (path[path.length() - 1] != '/'){
		curnode.path.push_back('/');
	}
// Check valid dir
	if (DIR * dirp = opendir(path.c_str())){
		struct dirent *dp = NULL;
		while (dp = readdir(dirp)){
			try{
			// Load stats, name
				curnode.name = dp->d_name;
				curnode.load(curnode.path + curnode.name);
			// Ignore self, parent
				if (
					(curnode.getname() != ".") &&
					(curnode.getname() != "..") &&
					(curnode.getname() != "./") &&
					(curnode.getname() != "../")
				){
				// If node is a dir, load children
					if (curnode.getisDirectory()){
						localsize += curnode.size = this->load(curnode.fullname);
					}
				// Load node
			// Ordered insertion
					container::iterator inpoint = this->contents.begin();
					for(
						container::iterator end = this->contents.end();
						inpoint != end;
						inpoint++
					){
						if (curnode.fullname < inpoint->fullname){
							break;
						}
					}
					this->contents.insert(inpoint, curnode);
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
	this->path = path;
	return localsize;
}

//******************
// dump(std::ostream&)
//	Dump contents, unfiltered, to std::ostream out
void FSModel::dump(std::ostream & out){
	out
		<< "Contents of " << this->path << std::endl
		<< "Type Size\tDate                     Name" << std::endl;
	for (
		container::iterator
			it = this->contents.begin(),
			end = this->contents.end();
		it != end;
		it++
	){
		it->dump(out);
	}
	out << "Total: " << this->getsize() << " elements" << std::endl;
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
	unsigned long maxsize, unsigned long minsize
){
	out
		<< "Contents of " << this->path << std::endl
		<< "Total: " << this->getsize() << " elements" << std::endl
		<< "Type Size\tDate                     Name" << std::endl;
	unsigned long found = 0;
	for (
		container::iterator
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
					(it->getsize() <= maxsize) &&
					(it->getsize() >= minsize)
				)
			)
		){
			it->dump(out);
			found++;
		}
	}
	out <<
		"Searching for \"" << expression << "\" in \"" << this->path
		<< "\" turned out  " << found << " results" << std::endl;
}

//**************************
// Getters
const container & FSModel::getcontents() const{
	return this->contents;
}
const std::string & FSModel::getpath() const{
	return this->path;
}
unsigned long FSModel::getsize() const{
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

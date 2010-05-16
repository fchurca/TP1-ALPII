#include "fsmodel.h"

#include <cstdlib>
#include <cstring>

#include <stdexcept>
#include <iostream>

using namespace std;

int main(int argc, char **argv){
	int ret = EXIT_SUCCESS;
	if (argc > 2){
		if (strcmp(argv[1], "-d")){
			cerr << "Expected \"-d\" as first parameter" << endl;
			ret = EXIT_FAILURE;
		}else try{
			FSModel mymodel;
			mymodel.load(argv[2]);
			mymodel.dump(cout);
			for(
				string expression;
				cin;
				mymodel.search(cout, expression)
			){
				getline(cin, expression);
			}
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
		cout << "Usage:\t" << argv[0] << " -d <path>" << endl;
	}
	return ret;
}

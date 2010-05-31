#include "tui.h"
#include "fsmodel.h"
#include "Cronometro.h"

#include <unistd.h>

#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char **argv){
	int ret = EXIT_SUCCESS;
	try{
		stringstream inputscript;
		FSModel mymodel;
		for(int c; (c = getopt(argc, argv, "d:")) != -1; ){
			try{
				switch (c){
				case 'd':
					inputscript << "load " << optarg << endl;
					break;
				}
			}catch(runtime_error e){
				cerr << e.what() << endl;
			}
		}
		parser(inputscript, cout, mymodel, false);
		cout << "Type \"help\"<return> for help" << endl;
		parser(cin, cout, mymodel);
	}catch(logic_error e){
		cerr << e.what() << endl << "Aborting" << endl;
		ret = EXIT_FAILURE;
	}catch(...){
		cerr << "Unknown exception. Aborting" << endl;
		ret = EXIT_FAILURE;
	}
	return ret;
}

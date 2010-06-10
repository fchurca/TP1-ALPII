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
		bool helped = false;
		for(int c; !helped && ((c = getopt(argc, argv, "d:e:so:h")) != -1); ){
			try{
				switch (c){
				case 'd':
					inputscript << "load " << optarg << endl;
					break;
				case 'e':
					inputscript << "expr " << optarg << endl;
					break;
				case 's':
					inputscript << "search" << endl;
					break;
				case 'o':
					inputscript << "logfile " << optarg << endl;
					break;
				case 'h':
					string usage(contents("usage"));
					helped = true;
					cout << usage;
					break;
				}
			}catch(runtime_error e){
				cerr << e.what() << endl;
			}
		}
		if (!helped){
			parser(inputscript, cout, mymodel, false);
			cout << "Type \"help\"<return> for help" << endl;
			parser(cin, cout, mymodel);
		}
	}catch(runtime_error e){
		cerr << e.what() << endl << "Aborting" << endl;
		ret = EXIT_FAILURE;
	}catch(logic_error e){
		cerr << e.what() << endl << "Aborting" << endl;
		ret = EXIT_FAILURE;
	}catch(...){
		cerr << "Unknown exception. Aborting" << endl;
		ret = EXIT_FAILURE;
	}
	return ret;
}

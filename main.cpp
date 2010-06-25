#include "tui.h"
#include "FSModel.h"
#include "Cronometro.h"

#include <unistd.h>

#include <cstdlib>
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
		bool interactive = true;
		for(int c; !helped && ((c = getopt(argc, argv, "d:e:M:m:sDo:hb")) != -1); ){
			try{
				switch (c){
				case 'd':
					inputscript << "load " << optarg << endl;
					break;
				case 'e':
					inputscript << "expr " << optarg << endl;
					break;
				case 'M':
					inputscript << "maxsize " << optarg << endl;
					break;
				case 'm':
					inputscript << "minsize " << optarg << endl;
					break;
				case 's':
					inputscript << "search" << endl;
					break;
				case 'D':
					inputscript << "dump" << endl;
					break;
				case 'o':
					inputscript << "logfile " << optarg << endl;
					break;
				case 'h':
					helped = true;
					cout << contents("usage");
					break;
				case 'b':
					interactive = false;
					break;
				}
			}catch(runtime_error e){
				cerr << e.what() << endl;
			}
		}
		if (!helped){
			parser(inputscript, cout, mymodel, false);
			if (interactive){
				parser(cin, cout, mymodel);
			}
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

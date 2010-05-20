#include "tui.h"

#include "fsmodel.h"
#include "Cronometro.h"

#include <cstdlib>
#include <cstring>

#include <stdexcept>
#include <iostream>

using namespace std;

int main(int argc, char **argv){
	int ret = EXIT_SUCCESS;
	FSModel mymodel;
	try{
// Stub for console parameter parser
//		for (int i = 1, next = 2; i < argc; i = next){
//			next++;
//		}
		if (argc > 2){
			if (!strcmp(argv[1], "-d")){
				Cronometro cron;
				mymodel.load(argv[2]);
				cron.parar();
				cout
					<< "Load finished: " << cron.getTiempoTranscurrido()
					<< " ms" << endl
					<< "Loaded " << mymodel.getsize() << " elements" << endl;
			}
		}
		cout << "Type \"help\"<return> for help" << endl;
		parser(cin, cout, mymodel);
	}catch(std::runtime_error e){
		mymodel.clear();
		cerr << e.what() << endl << "Aborting" << endl;
		ret = EXIT_FAILURE;
	}catch(...){
		mymodel.clear();
		cerr << "Unknown exception. Aborting" << endl;
		ret = EXIT_FAILURE;
	}
	return ret;
}

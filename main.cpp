#include "tui.h"

#include "fsmodel.h"
#include "Cronometro.h"

#include <stdexcept>
#include <iostream>

using namespace std;

int main(int argc, char **argv){
	int ret = EXIT_SUCCESS;
	try{
		FSModel mymodel;
		Cronometro cron;
		for (unsigned i = 1; i < argc; i++){
			try{
				cron.iniciar();
				mymodel.load(argv[i]);
				cron.parar();
				cout
					<< "Load finished: " << cron.getTiempoTranscurrido()
					<< " us" << endl
					<< "Loaded " << mymodel.getsize()
					<< " elements" << endl;
			}catch(runtime_error e){
				cerr << e.what() << endl;
			}
		}
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

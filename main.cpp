#include "fsmodel.h"
#include "Cronometro.h"

#include <ctime>

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
			Cronometro cron;
			mymodel.load(argv[2]);
			cron.parar();
			mymodel.dump(cout);
			cout
				<< "Load finished: " << cron.getTiempoTranscurrido() << " msec" << endl
				<< "Program terminates \
with EOF (control-D (*NIX) / control-Z (Windows/DOS))"
				<< endl;
			while (cin){
				string expression;
				cout << "Enter a search expression:" << endl;
				getline(cin, expression);
				if (cin){
					cron.iniciar();
					mymodel.search(cout, expression);
					cron.parar();
					cout
						<< "Search completed in "
						<< cron.getTiempoTranscurrido() << " msec" << endl;
				}
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
		cout
			<< "Usage:\t" << argv[0] << " -d <path>" << endl;
		;
	}
	return ret;
}

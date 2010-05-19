#include "fsmodel.h"
#include "Cronometro.h"

#include <ctime>

#include <cstdlib>
#include <cstring>

#include <stdexcept>
#include <iostream>
#include <sstream>

void parser(std::istream & in, std::ostream & out, FSModel & model);

using namespace std;

int main(int argc, char **argv){
	int ret = EXIT_SUCCESS;
	try{
		FSModel mymodel;
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
		parser(cin, cout, mymodel);
	}catch(std::runtime_error e){
		cerr << e.what() << endl << "Aborting" << endl;
		ret = EXIT_FAILURE;
	}catch(std::exception e){
		cerr << e.what() << endl << "Aborting" << endl;
	}catch(...){
		cerr << "Unhandled exception" << endl << "Aborting" << endl;
		ret = EXIT_FAILURE;
	}
	return ret;
}

void parser(std::istream & in, std::ostream & out, FSModel & model){
	Cronometro cron;
	string expression;
	unsigned long
		minsize = 0,
		maxsize = -1;
	while (cin){
		string dump, command;
		stringstream ss;
		out << "> ";
		getline(cin, dump);
		ss << dump;
		ss >> command;
		if (command == "exit"){
			return;
		}else if (command == "dump"){
			model.dump(out);
		}else if (command == "expression"){
			ss >> ws;
			getline(ss, expression);
		}else if (command == "load"){
			ss >> ws;
			getline(ss, dump);
			model.clear();
			model.load(dump);
		}else if (command == "maxsize"){
			ss >> dump;
			maxsize = atol(dump.c_str());
		}else if (command == "minsize"){
			ss >> dump;
			minsize = atol(dump.c_str());
		}else if (command == "search"){
			cron.iniciar();
			model.search(out, expression, maxsize, minsize);
			cron.parar();
			out
				<< "Search completed in "
				<< cron.getTiempoTranscurrido() << " msec" << endl;
		}else if (command == "status"){
			out
				<< "Path:         " << model.getpath() << endl
				<< "Expression:   " << expression << '\"' << endl
				<< "Minimum size: " << minsize << endl
				<< "Maximum size: " << maxsize << endl;
		}
	}	
}

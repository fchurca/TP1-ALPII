#include "tui.h"
#include "Cronometro.h"

#include <climits>

#include <stdexcept>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

std::string contents(std::string file){
	string ret;
	ifstream infile(file.c_str());
	string dump;
	if (!infile){
		throw runtime_error(file + " not found");
	}
	while (infile){
		getline(infile, dump);
		if (infile){
			ret += dump + '\n';
		}
	}
	return ret;
}

std::string cleanup(std::string s){
	if (
		((s[0] == '"') && (s[s.length() - 1] == '"')) ||
		((s[0] == '\'') && (s[s.length() - 1] == '\''))
	){
		s.erase(0, 1);
		s.erase(s.length() - 1, 1);
	}
	return s;
}

void parser(
	istream & in, ostream & out,
	FSModel & model,
	bool showprompt
){
	string S_help(contents("help"));
	Cronometro cron;
	string expression = "*";
	unsigned long long
		minsize = 0,
		maxsize = ULLONG_MAX;
	while (in){	
		try{
			string dump, command;
			stringstream ss;
			if(showprompt){
				out << "> ";
			}
			getline(in, dump);
			ss << dump;
			ss >> command;
			if (command == "dump"){
				model.dump(out);
			}else if (command == "exit"){
				return;
			}else if (command == "expr"){
				ss >> ws;
				getline(ss, expression);
				expression = cleanup(expression);
			}else if (command == "help"){
				out << S_help;
			}else if (command == "load"){
				ss >> ws;
				getline(ss, dump);
				model.clear();
				cron.iniciar();
				model.load(cleanup(dump));
				cron.parar();
				out
					<< "Load finished: " << cron.getTiempoTranscurrido()
					<< " us" << endl
					<< "Loaded " << model.getsize()
					<< " elements" << endl;
			}else if (command == "maxsize"){
				ss >> dump;
				maxsize = atol(dump.c_str());
			}else if (command == "minsize"){
				ss >> dump;
				minsize = atol(dump.c_str());
			}else if (command == "nomax"){
				maxsize = ULLONG_MAX;
			}else if (command == "nomin"){
				minsize = 0;
			}else if (command == "search"){
				cron.iniciar();
				model.search(out, expression, maxsize, minsize);
				cron.parar();
				out
					<< "Search completed in "
					<< cron.getTiempoTranscurrido() << " us" << endl;
			}else if (command == "status"){
				out
					<< "Path:\t\t\"" << model.getpath() << '\"' << endl
					<< "Total files:\t" << model.getsize() << endl
					<< "Expression:\t\"" << expression << '\"' << endl
					<< "Minimum size:\t";
				if (minsize){
					out << minsize;
				}else{
					out << "(none)";
				}
				out << endl << "Maximum size:\t";
				if (maxsize < ULLONG_MAX) {
					out << maxsize << endl;
				}else{
					out << "(none)";
				}
				out << endl;
			}else{
				if (command.length()){
					out << command << ": command not found" << endl;
				}
			}
		}catch(runtime_error e){
			cerr << e.what() << endl;
		}
	}
}

#include "tui.h"
#include "Cronometro.h"
#include "FSModel.h"

#include <climits>

#include <stdexcept>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

std::string contents(const std::string & file){
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
	static string S_help(contents("help"));
	Cronometro cron;
	static string
		expression = "*",
		logfilename;
	unsigned long long
		minsize = 0,
		maxsize = ULLONG_MAX;
	ofstream log;
	while (in){
		try{
			string
				dump,
				command;
			stringstream ss;
			if(showprompt){
				out << "> ";
			}
			getline(in, dump);
			ss << dump;
			ss >> command;
			if (command == "dump"){
				model.dump(out);
				if(log.is_open()){
					model.dump(log);
				}
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
				if(log.is_open()){
					log
						<< "Load finished: " << cron.getTiempoTranscurrido()
						<< " us" << endl
						<< "Loaded " << model.getsize()
						<< " elements" << endl;
				}
			}else if (command == "logfile"){
				ss >> ws;
				getline(ss, logfilename);
				logfilename = cleanup(logfilename);
				if (log.is_open()){
					log.close();
				}
				log.open(logfilename.c_str(), ofstream::app);
			}else if (command == "maxsize"){
				ss >> maxsize;
			}else if (command == "minsize"){
				ss >> minsize;
			}else if (command == "noexpr"){
				expression = "*";
			}else if (command == "nolog"){
				logfilename.clear();
				if (log.is_open()){
					log.close();
				}
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
				if(log.is_open()){
					model.search(log, expression, maxsize, minsize);
					log
						<< "Search completed in "
						<< cron.getTiempoTranscurrido() << " us" << endl;
				}
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
					out << maxsize;
				}else{
					out << "(none)";
				}
				out << endl << "Log file:\t";
				if (logfilename.length()){
					out << '\"' << logfilename << '\"';
				}else{
					out << "(none)";
				}
				out << endl;
				if(log.is_open()){
					log
						<< "Path:\t\t\"" << model.getpath() << '\"' << endl
						<< "Total files:\t" << model.getsize() << endl
						<< "Expression:\t\"" << expression << '\"' << endl
						<< "Minimum size:\t";
					if (minsize){
						log << minsize;
					}else{
						log << "(none)";
					}
					log << endl << "Maximum size:\t";
					if (maxsize < ULLONG_MAX) {
						log << maxsize;
					}else{
						log << "(none)";
					}
					log << endl << "Log file:\t";
					if (logfilename.length()){
						log << '\"' << logfilename << '\"';
					}else{
						log << "(none)";
					}
					log << endl;
				}
			}else{
				if (command.length()){
					out << command << ": command not found" << endl;
				}
			}
		}catch(runtime_error e){
			cerr << e.what() << endl;
		}
	}
	if (log.is_open()){
		log.close();
	}
}

#include "tui.h"
#include "Cronometro.h"

#include <string>
#include <sstream>

using namespace std;

string cleanup(string s){
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
	Cronometro cron;
	string expression = "*";
	unsigned long
		minsize = 0,
		maxsize = -1;
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
				out << "\
Command\tParameter\tDescription\n\
dump\t(none)\t\tDump directory contents\n\
exit\t(none)\t\tExit the program\n\
help\t(none)\t\tShow help\n\
search\t(none)\t\tShow matching fles\n\
status\t(none)\t\tShow current search criteria\n\
expr\texpression\tSave search expression\n\
load\tdirectory\tLoad directory contents\n\
maxsize\tsize\t\tMaximum file size in bytes (-1 for no restriction)\n\
minsize\tsize\t\tMinimum file size in bytes (0 for no restriction)\n\
";
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
					<< "Minimum size:\t" << minsize << endl
					<< "Maximum size:\t" << maxsize << endl;
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

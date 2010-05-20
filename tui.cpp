#include "tui.h"

#include <string>
#include <sstream>

void parser(std::istream & in, std::ostream & out, FSModel & model){
	Cronometro cron;
	std::string expression;
	unsigned long
		minsize = 0,
		maxsize = -1;
	while (in){
		std::string dump, command;
		std::stringstream ss;
		out << "> ";
		std::getline(in, dump);
		ss << dump;
		ss >> command;
		if (command == "dump"){
			model.dump(out);
		}else if (command == "exit"){
			return;
		}else if (command == "expr"){
			ss >>std:: ws;
			std::getline(ss, expression);
		}else if (command == "help"){
			out
<< "Command Parameter   Description\n"
<< "dump    (none)      Dump directory contents\n"
<< "exit    (none)      Exit the program\n"
<< "expr    expression  Save search expression\n"
<< "help    (none)      Show help\n"
<< "load    directory   Load directory contents\n"
<< "maxsize size        Maximum file size in bytes (-1 for no restriction)\n"
<< "minsize size        Minimum file size in bytes (0 for no restriction)\n"
<< "search  (none)      Show matching fles\n"
<< "status  (none)      Show current search criteria\n";
		}else if (command == "load"){
			ss >> std::ws;
			std::getline(ss, dump);
			model.clear();
			cron.iniciar();
			model.load(dump);
			cron.parar();
			out
				<< "Load completed in "
				<< cron.getTiempoTranscurrido() << " msec" << std::endl;
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
				<< cron.getTiempoTranscurrido() << " msec" << std::endl;
		}else if (command == "status"){
			out
				<< "Path:         \"" << model.getpath() << '\"' << std::endl
				<< "Expression:   \"" << expression << '\"' << std::endl
				<< "Minimum size: " << minsize << std::endl
				<< "Maximum size: " << maxsize << std::endl;
		}else{
			out << command << " not a valid command" << std::endl;
		}
	}
}

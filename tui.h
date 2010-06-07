#ifndef __TUI_H__
#define __TUI_H__

#include "fsmodel.h"
#include "Cronometro.h"

#include <string>
#include <iostream>

std::string contents(std::string file);

std::string cleanup(std::string s);

void parser(
	std::istream & in, std::ostream & out,
	FSModel & model,
	bool showprompt = true
);

#endif	//	__TUI_H__

#ifndef __TUI_H__
#define __TUI_H__

#include "FSModel.h"

#include <string>
#include <iostream>

std::string contents(const std::string & file);

std::string cleanup(std::string s);

void parser(
	std::istream & in, std::ostream & out,
	FSModel & model,
	bool showprompt = true
);

#endif	//	__TUI_H__

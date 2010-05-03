#include "expr.h"

#include <cstring>

using namespace std;

#ifdef EXPR_DEBUG
#include <iostream>
#include <cstdlib>

int main(int argc, char **argv){
	string expression, input;
	cout << "Enter expression to match:" << endl;
	getline(cin, expression);
	cout << "Enter string where to look up the expression:" << endl;
	getline(cin, input);
	cout << "The string \"" << input << "\" "
		<< (MatchesExpression(expression, input)? "matches" : "does not match")
		<< " the expression \"" << expression << '\"' << endl;
	return EXIT_SUCCESS;
}
#endif

bool MatchesExpression(const std::string expression, const std::string input){
	return MatchesExpression(expression.c_str(), input.c_str());
}
bool MatchesExpression(const char * expression, const char * input){
	if(!(expression or input)) return true;		// If only one is NULL abort
	if(!(expression and input)) return false;	// If both are NULL, success
	size_t
		exprlen = strlen(expression),
		usefullen = strcspn(expression, "*?");
	char * newexpr = new char[usefullen + 1];
	strncpy(newexpr, expression, usefullen); newexpr[usefullen] = 0;
	bool ret= strstr(newexpr, input);
/* TODO:
If we have to recognize asterisks and question marks as part of string contents:
	* Provide escaping version for strcspn ("\?", "\*")
	* Copy expression with escaped chars (remove '\'s not preceded by '\')
*/
/* TODO:
If we do find the expression (ret), recurr to self for later.
Else, continue looking until we reach the end of the input.
*/
	delete[] newexpr;
	return usefullen ? ret : !*input;
}

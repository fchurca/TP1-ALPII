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
	if(!(expression and input)) return false;	// If any is NULL abort
	size_t
		exprlen = strlen(expression),
		usefullen = strcspn(expression, "*?");
/* TODO
If we have to recognize asterisks and question marks as part of string contents:
	* Provide escaping version for strcspn ("\?", "\*")
	* Copy expression with escaped chars (remove '\'s not preceded by '\')
*/
	char * newexpr = new char[usefullen + 1];
	strncpy(newexpr, expression, usefullen); newexpr[usefullen] = 0;
	bool ret;
	switch (*expression){
		case '*':
/* TODO
Provide '*' wildcard solving.
Recursive, using strstr() ?
*/
			ret = false;
			break;
		case '?':
			ret = *input ? MatchesExpression(expression + 1, input + 1) : false;
			break;
		case 0:
			ret = !*input;
			break;
		default:
			ret = !strncmp(newexpr, input, usefullen);
			if (ret) ret = MatchesExpression(expression + usefullen, input + usefullen);
	}
	delete[] newexpr;
	return ret;
}

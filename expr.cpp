#include "expr.h"

#include <cstring>

/***************************************
* MatchesExpression()
*	Checks if the cstring input matches the search expression cstring expression
*	Supported wildcards:
*		'*'	: any string
*		'?'	: any char
***************************************/
bool MatchesExpression(const char * expression, const char * input){
	bool ret = false;
// If none is NULL go on
	if(expression && input){
		switch (*expression){
		// "Any string" wildcard
			case '*':
				expression++;
			// Check only once if another '*' follows in the expression
				if (expression[2] == '*')
					ret = MatchesExpression(expression, input);
			// If next isn't '*'...
				else if (expression[1])
				// ...until we find a match or we run out of input...
					while((!ret) && *input)
					// ...try the rest of the expression for each substring
						ret = MatchesExpression(expression, input++);
			// Match if the input is an empty string
				else
					ret = true;
				break;
		// "Any char" wildcard
			case '?':
			// If there is a character, jump over it
				if (*input)
					ret = MatchesExpression(expression + 1, input + 1);
				break;
		// Expression has ended
			case 0:
			// If the string has ended, match
				ret = ! *input;
				break;
		// First character isn't wildcard
			default:
			// Length of expression to first of: end or first wildcard
				size_t usefullen = strcspn(expression, "*?");
			// Check if characters up to wildcard or end are same
				if (ret = ! strncmp(expression, input, usefullen))
				// In that case, continue checking from there on
					ret = MatchesExpression(expression + usefullen, input + usefullen);
		}
// If both are NULL, match. Else, leave ret = false from init and abort.
	} else if (expression == input)
		ret = true;
	return ret;
}

//**************************************
// Wrapper for using MatchesExpression() with std::string
bool MatchesExpression(const std::string &expression, const std::string &input){
	return MatchesExpression(expression.c_str(), input.c_str());
}

//**************************************
// main() for debugging

#ifdef EXPR_DEBUG

#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv){
	string expression, input;
	while(cin){
		cout << "Enter expression to match:" << endl;
		getline(cin, expression);
		cout << "Enter string where to look up the expression:" << endl;
		getline(cin, input);
		cout << "The string \"" << input << "\" "
			<< (
				MatchesExpression(expression, input)
					? "matches"
					: "does not match"
				)
			<< " the expression \"" << expression << '\"' << endl;
	}
	return EXIT_SUCCESS;
}

#endif

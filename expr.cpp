#include "expr.h"

#include <cstring>

//**************************************
// MatchesExpression()
//	Checks if the input matches the search expression
//	Supported wildcards:
//		'*'	: any string
//		'?'	: any char
bool MatchesExpression(const char * expression, const char * input){
// Assume mismatch
	bool ret = false;
// If none is NULL go on. If any or both are NULL, leave mismatch.
	if (expression && input){
	// According to first character of expression:
		switch (*expression){
		// "Any string" wildcard
			case '*':
			// If there is something else to match
				if (expression[1]){
				// Go to the rest of the expression
					expression++;
				// If the input is not an empty string...
					if (*input){
						do {
						// ...try the rest of the expression for each substring
							ret = MatchesExpression(expression, input++);
						} while ((!ret) && *input);
					// ...until we find a match or we run out of input.
				// Match if the input is an empty string
					}else{
						ret = true;
					}
			// If expression was only "*", match any string
				}else{
					ret = true;
				}
				break;
		// "Any char" wildcard
			case '?':
			// If there is a character, jump over it
				if (*input){
					ret = MatchesExpression(expression + 1, input + 1);
				}
				break;
		// Expression has ended
			case 0:
			// Match if the string has ended
				ret = ! *input;
				break;
		// First character isn't wildcard nor has the expression ended
			default:
			// If first characters are same, recurr
				if (*expression == *input){
					ret = MatchesExpression(expression + 1, input + 1);
				}
		}
	}
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
	while (cin){
		cout << "Enter expression to match:" << endl;
		getline(cin, expression);
		cout << "Enter string where to look up the expression:" << endl;
		getline(cin, input);
		cout
			<< "The string \"" << input << "\" "
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

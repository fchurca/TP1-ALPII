#include <string>

/***************************************
* MatchesExpression()
*	Checks if the cstring input matches the search expression cstring expression
*	Supported wildcards:
*		'*'	: any string
*		'?'	: any char
***************************************/
bool MatchesExpression(const char * expression, const char * input);

//**************************************
// Wrapper for using MatchesExpression() with std::string
bool MatchesExpression(const std::string &expression, const std::string &input);

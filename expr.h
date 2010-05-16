#include <string>

//**************************************
// MatchesExpression()
//	Checks if the input matches the search expression
//	Supported wildcards:
//		'*'	: any string
//		'?'	: any char
bool MatchesExpression(const char * expression, const char * input);

//**************************************
// Wrapper for using MatchesExpression() with std::string
bool MatchesExpression(const std::string &expression, const std::string &input);

//parses the scene data

#ifndef Parser_h
#define Parser_h

#include <string>

class Parser
{
	//vars
public:

	unsigned long sourceLength = 0, sourcePos = 0;
	unsigned char lastChar, currentChar;
	unsigned int lineCount = 0, charCount = 0;

	std::string source = "";

	//methods
public:

	//Constructor
	Parser(const std::string& data) :source(data) { sourceLength = source.length(); }

	//gets the next char
	char GetNextChar();
	//peeks at the next char but does not move up
	char PeekNextChar();
};

#endif

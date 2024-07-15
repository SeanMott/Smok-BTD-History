#include "Parser.h"

using namespace std;

char Parser::GetNextChar()
{
	//end of file
	if (sourcePos + 1 == sourceLength)
		return -1;

	if (sourcePos > 0)
		lastChar = currentChar;

	//sourcePos++;
	currentChar = source[sourcePos++];

	return currentChar;
}

char Parser::PeekNextChar()
{
	//end of file
	if (sourcePos + 1 == sourceLength)
		return -1;

	return source[sourcePos + 1];
}

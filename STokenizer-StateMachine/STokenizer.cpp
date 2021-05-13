#include "STokenizer.h"

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];


STokenizer& operator>>(STokenizer& s, Token& t)
{
	string str;
	
	s.get_token(0, str);

	t = Token(str, get_type(str, s._table));
	return s;
}

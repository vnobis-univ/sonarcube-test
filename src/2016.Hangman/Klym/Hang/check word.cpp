

#include <string>

bool checkLetter( char &k, std::string &word, std::string &hWord )
{
	int hitCount = 0;

	for( unsigned int index = 0; index < word.length(); ++index )
	{
		if( k == tolower( word[ index ] ) )
		{
			hWord[ index ] = word[ index ];
			++hitCount;
		}
	}

	if( hitCount > 0 )
		return true;
	else
		return false;
}
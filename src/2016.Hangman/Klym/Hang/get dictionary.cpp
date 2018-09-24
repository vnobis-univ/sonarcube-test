

#include "Global.h"

#include <fstream>
#include <vector>

bool getDictionary( std::vector< std::string > &v )
{
	std::ifstream inFile;

	inFile.open( "dictionary.txt", std::ios::in );

	if( inFile.is_open() )
	{
		std::string input;

		while( inFile.good() )
		{
			std::getline( inFile, input, '\n' );

			v.push_back( input );
		}

		inFile.close();
		return true;
	}

	con.wait( "Unable to open dictionary.txt" );
	return false;
}
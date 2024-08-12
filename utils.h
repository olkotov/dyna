// Oleg Kotov

#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <string>

template<class ElementType>
bool addUnique( std::vector<ElementType>& vector, const ElementType& element )
{
	for ( const auto& entry : vector )
	{
		if ( entry == element ) return false;
	}

	vector.push_back( element );
	return true;
}

template<class ElementType>
bool removeSwap( std::vector<ElementType>& vector, const ElementType& element )
{
	auto iter = std::find( vector.begin(), vector.end(), element );

	if ( iter != vector.end() )
	{
		std::iter_swap( iter, vector.end() - 1 );
		vector.pop_back();

		return true;
	}

	return false;
}

std::string readTextFromFile( const std::string& filePath );


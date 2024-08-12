// Oleg Kotov

#pragma once

#include <string.h>
#include <iostream>

class Mat3
{
public:

	Mat3() 
		: m_data
		{ 
			{ 1.0f, 0.0f, 0.0f }, 
			{ 0.0f, 1.0f, 0.0f }, 
			{ 0.0f, 0.0f, 1.0f }
		} 
	{}

	Mat3( std::initializer_list<float> mat )
	{
		auto itr = mat.begin();

		for ( int8_t i = 0; i < 3; ++i )
		{
			for ( int8_t j = 0; j < 3; ++j )
			{
				m_data[i][j] = *itr++;
			}
		}
	}

	Mat3( std::initializer_list<std::initializer_list<float>> mat )
	{
		auto row = mat.begin();

		for ( int8_t i = 0; i < 3; ++i )
		{
			auto col = ( *row++ ).begin();
			
			for ( int8_t j = 0; j < 3; ++j )
			{
				m_data[i][j] = *col++;
			}
		}
	}

	Mat3( float mat[3][3] )
	{
		memcpy( m_data, mat, sizeof( m_data ) );
	}

	Mat3& operator=( float mat[3][3] )
	{
		memcpy( m_data, mat, sizeof( m_data ) );
		return *this;
	}

	void print() const
	{
		for ( int8_t i = 0; i < 3; ++i )
		{
			for ( int8_t j = 0; j < 3; ++j )
			{
				std::cout << m_data[i][j] << " ";
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;
	}

public:

	static const Mat3 identity;
	static const Mat3 not_identity;
	static const Mat3 not_identity_2;

protected:

	float m_data[3][3];
};

const Mat3 Mat3::identity = Mat3();
const Mat3 Mat3::not_identity = { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } };
const Mat3 Mat3::not_identity_2 = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };


// Oleg Kotov

#include "utils.h"

std::string readTextFromFile( const std::string& filePath )
{
	// Открытие файла в режиме чтения
	std::ifstream file( filePath );

	// Проверка, что файл успешно открыт
	if ( !file.is_open() )
	{
		throw std::runtime_error( "Unable to open file: " + filePath );
	}

	// Чтение содержимого файла в строку
	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string fileContent = buffer.str();

	// Закрытие файла
	file.close();

	return fileContent;
}


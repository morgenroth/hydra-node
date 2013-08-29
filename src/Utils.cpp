/*
 * Utils.cpp
 *
 *  Created on: 29.08.2013
 *      Author: morgenro
 */

#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>

Utils::Utils() {
}

Utils::~Utils() {
}

void Utils::rtrim(std::string &str)
{
	// trim trailing spaces
	std::string::size_type endpos = str.find_last_not_of(" \t");
	if( std::string::npos != endpos )
	{
		str = str.substr( 0, endpos+1 );
	}
}

void Utils::ltrim(std::string &str)
{
	// trim leading spaces
	std::string::size_type startpos = str.find_first_not_of(" \t");
	if( std::string::npos != startpos )
	{
		str = str.substr( startpos );
	}
}

void Utils::trim(std::string &str)
{
	ltrim(str);
	rtrim(str);
}

std::vector<std::string> Utils::tokenize(const std::string &token, const std::string &data, const std::string::size_type max)
{
	std::vector<std::string> l;
	std::string value;

	// Skip delimiters at beginning.
	std::string::size_type pos = data.find_first_not_of(token, 0);

	std::string::size_type tokenPos = 0;

	while (pos != std::string::npos)
	{
		if (l.size() >= max)
		{
			// if maximum reached
			tokenPos = std::string::npos;
		}
		else
		{
			// Find first "non-delimiter".
			tokenPos = data.find_first_of(token, pos);
		}

		if (tokenPos == std::string::npos) {
			// No more tokens found, add last part to the vector.
			value = data.substr(pos);
			l.push_back(value);

			// exit the loop
			break;
		} else {
			// Found a token, add it to the vector.
			value = data.substr(pos, tokenPos - pos);
			l.push_back(value);
		}
		// Skip delimiters.  Note the "not_of"
		pos = data.find_first_not_of(token, tokenPos);
	}

	return l;
}

std::string Utils::readSysFile(const std::string &filename)
{
	std::ifstream sysfile_stream(filename.c_str());
	std::stringstream ss;
	ss << sysfile_stream.rdbuf();

	std::string buffer = ss.str();
	buffer.erase(buffer.begin() + (buffer.length() - 1));

	return buffer;
}

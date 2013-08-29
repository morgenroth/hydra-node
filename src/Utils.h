/*
 * Utils.h
 *
 *  Created on: 29.08.2013
 *      Author: morgenro
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <vector>

class Utils {
public:
	Utils();
	virtual ~Utils();

	static std::string readSysFile(const std::string &filename);

	static void rtrim(std::string &str);
	static void ltrim(std::string &str);
	static void trim(std::string &str);

	static std::vector<std::string> tokenize(const std::string &token, const std::string &data, const std::string::size_type max = std::string::npos);
};

#endif /* UTILS_H_ */

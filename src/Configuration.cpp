/*
 * Configuration.cpp
 *
 *  Created on: 14.01.2011
 *      Author: morgenro
 */

#include "Configuration.h"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>

Configuration::Configuration()
{
}

Configuration::~Configuration()
{
}

Configuration& Configuration::getInstance()
{
	static Configuration conf;
	return conf;
}

void Configuration::setInterface(const ibrcommon::vinterface &iface)
{
	_iface = iface;
}

const std::string Configuration::getHostname() const
{
	char *hostname_array = new char[64];

	if ( gethostname(hostname_array, 64) != 0 )
	{
		// error
		delete[] hostname_array;
		return "unknown";
	}

	std::string hostname(hostname_array);
	delete[] hostname_array;

	return hostname;
}

const std::string Configuration::getId() const
{
	const std::string dev_addr_path = "/sys/class/net/" + _iface.toString() + "/address";

	std::ifstream dev_addr(dev_addr_path.c_str());
	std::stringstream ss;
	ss << dev_addr.rdbuf();

	std::string buffer = ss.str();
	buffer.erase(buffer.begin() + (buffer.length() - 1));

	return buffer;
}

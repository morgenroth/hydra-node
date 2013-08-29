/*
 * HostControl.cpp
 *
 *  Created on: 17.01.2011
 *      Author: morgenro
 */

#include "HostControl.h"
#include <ibrcommon/appstreambuf.h>
#include <iostream>
#include <cstdlib>

HostControl& HostControl::getInstance()
{
	static HostControl hc;
	return hc;
}

HostControl::HostControl()
 : _harmless(false)
{
}

HostControl::~HostControl()
{
}

void HostControl::shutdown() const
{
	std::cout << "shutdown the node" << std::endl;

	if (!_harmless)
	{
		::system("halt");
	}
}

void HostControl::system(const std::string &cmd, std::ostream &output) const
{
	std::cout << "system call: " << cmd << std::endl;

	if (!_harmless)
	{
		ibrcommon::appstreambuf app(cmd, ibrcommon::appstreambuf::MODE_READ);
		std::iostream stream(&app);
		output << stream.rdbuf();
	}
}

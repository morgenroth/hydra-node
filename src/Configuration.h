/*
 * Configuration.h
 *
 *  Created on: 14.01.2011
 *      Author: morgenro
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <string>
#include <ibrcommon/net/vinterface.h>

class Configuration
{
public:
	Configuration();
	virtual ~Configuration();

	void setInterface(const ibrcommon::vinterface &iface);

	const std::string getHostname() const;
	const std::string getId() const;

	static Configuration& getInstance();

private:
	ibrcommon::vinterface _iface;

};

#endif /* CONFIGURATION_H_ */

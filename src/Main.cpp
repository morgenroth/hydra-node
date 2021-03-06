/*
 * Main.cpp
 *
 *  Created on: 14.01.2011
 *      Author: morgenro
 */

#include "Configuration.h"
#include "DiscoverComponent.h"
#include "CommandServer.h"
#include "FakeGPS.h"
#include "ClockMonitor.h"

#include <ibrcommon/net/vinterface.h>

#include <cstdlib>
#include <iostream>
#include <getopt.h>
#include <unistd.h>

void print_help()
{
	std::cout << "-- HydraNode --" << std::endl;
	std::cout << "Syntax: hnd [options]"  << std::endl;
	std::cout << std::endl;
	std::cout << "* parameters *" << std::endl;
	std::cout << " -h      display this text" << std::endl;
	std::cout << " -g      enable GPS emulation" << std::endl;
	std::cout << " -p      tcp port for incoming control connections (default: 3486)" << std::endl;
	std::cout << " -d      discovery port (default: 3232)" << std::endl;
	std::cout << " -n      host identifier (default: hostname)" << std::endl;
	std::cout << " -i      discovery interface (default: lo)" << std::endl;
	std::cout << " -t      ntp server for clock measurements" << std::endl;
}

int main(int argc, char** argv)
{
	// get a configuration object
	Configuration &conf = Configuration::getInstance();

	int opt = 0;
	std::string p_hostname = conf.getHostname();
	std::string p_iface = "lo";
	std::string p_ntpserver = "127.0.0.1";
	bool p_gps = false;
	unsigned int _p_disco_port = 3232;
	unsigned int _p_port = 3486;

	while((opt = ::getopt(argc, argv, "hd:vgp:n:i:t:")) != -1)
	{
		switch (opt)
		{
		case 'h':
			print_help();
			return 0;

		case 'd':
			_p_disco_port = ::atoi(optarg);
			break;

		case 'p':
			_p_port = atoi(optarg);
			break;

		case 'g':
			p_gps = true;
			break;

		case 'n':
			p_hostname = optarg;
			break;

		case 'i':
			p_iface = optarg;
			break;

		case 't':
			p_ntpserver = optarg;
			break;

		default:
			std::cout << "unknown command" << std::endl;
			return -1;
		}
	}

	// some output for the user
	std::cout << "startup of hydra node daemon" << std::endl;
	std::cout << "hostname: " << p_hostname << std::endl;

	// listen on interface
	const ibrcommon::vinterface iface(p_iface);
	conf.setInterface(iface);

	// create a fake gps
	FakeGPS &gps = FakeGPS::getInstance();
	if (!p_gps) gps.disable();

	// create clock monitor instance
	ClockMonitor &cm = ClockMonitor::getInstance();
	cm.setReference(p_ntpserver);
	cm.start();

	// listen on incoming tcp connections
	CommandServer srv(_p_port);
	srv.start();

	while (true)
	{
		try {
			// run discovery module
			DiscoverComponent disco(p_hostname, _p_disco_port, iface);
			disco.run();
		} catch (const std::exception&) {
			// error retry in 2 seconds
			std::cout << "can not listen on multicast socket" << std::endl;
			ibrcommon::Thread::sleep(2000);
		}
	}
}

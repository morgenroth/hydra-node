/*
 * CommandServer.cpp
 *
 *  Created on: 14.01.2011
 *      Author: morgenro
 */

#include "config.h"
#include "CommandServer.h"
#include "HostControl.h"
#include "FakeGPS.h"
#include "Utils.h"
#include "Configuration.h"
#include "ctrl/LevelZero.h"

#include <ibrcommon/thread/MutexLock.h>
#include <netinet/in.h>


CommandServer::Connection::Connection(ibrcommon::clientsocket *client, ibrcommon::Conditional &m, unsigned int &c)
 : _stream(client), _active_connections_cond(m), _active_connections(c)
{
	ibrcommon::MutexLock l(_active_connections_cond);
	_active_connections++;
	_active_connections_cond.signal(true);
}

CommandServer::Connection::~Connection()
{
	ibrcommon::MutexLock l(_active_connections_cond);
	_active_connections--;
	_active_connections_cond.signal(true);
}

void CommandServer::Connection::setup() throw ()
{
	std::cout << "connection up" << std::endl;
}

void CommandServer::Connection::run() throw ()
{
	Configuration &conf = Configuration::getInstance();

	ctrl::CommandSet *entry = ctrl::LevelZero::getInstance();

	// send 'welcome'
	_stream << PACKAGE_STRING << " " << conf.getHostname() << " " << conf.getId() << std::endl;

	// read and execute the given script
	std::string buffer;

	// read script lines
	while (_stream.good())
	{
		// get the next line
		getline(_stream, buffer);

		// search for '\r\n' and remove the '\r'
		std::string::reverse_iterator iter = buffer.rbegin();
		if ( (*iter) == '\r' ) buffer = buffer.substr(0, buffer.length() - 1);

		// received a new command
		//std::cout << "[] " << buffer << std::endl;

		// exit if EOF was received
		if (buffer.find("quit") == 0) break;

		ctrl::CommandSet *sub = entry;

		do {
			// split buffer into words
			std::vector<std::string> words = Utils::tokenize(" ", buffer, 1);

			// abort if there are no more words
			if (words.size() <= 0) {
				ctrl::CommandSet::result(_stream, 404, "COMMAND NOT FOUND");
				break;
			}

			// get next level for the given command
			sub = sub->enter(words[0]);

			if (sub == NULL) {
				ctrl::CommandSet::result(_stream, 404, "COMMAND NOT FOUND");
				break;
			}
			else if (sub->isCommand()) {
				sub->execute(words[1], _stream);
				break;
			}

			// assign remaining part to the buffer
			buffer = words[1];
		} while (sub != NULL);
	}
}

void CommandServer::Connection::finally() throw ()
{
	_stream.close();
	std::cout << "connection down" << std::endl;
}

void CommandServer::Connection::__cancellation() throw ()
{
}

CommandServer::CommandServer(unsigned int port)
 : _srv(port, 5), _running(true), _active_connections(0)
{
}

CommandServer::~CommandServer()
{
	// wait until all connections are closed
	ibrcommon::MutexLock l(_active_connections_cond);
	while (_active_connections > 0) _active_connections_cond.wait();
}

void CommandServer::setup() throw ()
{
	_srv.up();
}

void CommandServer::run() throw ()
{
	while (_running)
	{
		ibrcommon::vaddress client_addr;
		ibrcommon::clientsocket *client = _srv.accept(client_addr);

		CommandServer::Connection *conn = new CommandServer::Connection(client, _active_connections_cond, _active_connections);
		conn->start();
	}
}

void CommandServer::finally() throw ()
{
	_srv.close();
}

void CommandServer::__cancellation() throw ()
{
	_srv.down();
}

/*
 * LevelDtnd.cpp
 *
 *  Created on: 29.08.2013
 *      Author: morgenro
 */

#include "ctrl/LevelDtnd.h"
#include <ibrcommon/net/vaddress.h>
#include <ibrcommon/net/socket.h>
#include <ibrcommon/net/socketstream.h>
#include <sstream>

namespace ctrl {

	LevelDtnd::LevelDtnd(CommandSet *parent)
	 : CommandSet(parent, "dtnd")
	{
	}

	LevelDtnd::~LevelDtnd()
	{
	}

	bool LevelDtnd::isCommand() const
	{
		return true;
	}

	void LevelDtnd::execute(const std::string &parameters, std::iostream &stream) const
	{
		// connect to the daemon
		ibrcommon::vaddress addr("localhost", 4550);
		ibrcommon::socketstream client(new ibrcommon::tcpsocket(addr));

		std::string buffer;

		// read welcome
		getline(client, buffer);

		client << "protocol management" << std::endl;

		// read protocol switch ack
		getline(client, buffer);

		client << parameters << std::endl;

		// read command ack
		getline(client, buffer);

		// search for '\r\n' and remove the '\r'
		std::string::reverse_iterator iter = buffer.rbegin();
		if ( (*iter) == '\r' ) buffer = buffer.substr(0, buffer.length() - 1);

		// check return code
		int code = 0;
		std::stringstream ss(buffer);
		ss >> code;

		if (code != 200) {
			result_fail(stream);
			return;
		}

		result_listing(stream);

		while (client.good()) {
			getline(client, buffer);

			// search for '\r\n' and remove the '\r'
			std::string::reverse_iterator iter = buffer.rbegin();
			if ( (*iter) == '\r' ) buffer = buffer.substr(0, buffer.length() - 1);

			if (buffer.length() == 0) break;

			stream << buffer << std::endl;
		}

		result_done(stream);
	}

} /* namespace ctrl */

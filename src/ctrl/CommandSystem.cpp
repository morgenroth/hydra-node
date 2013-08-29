/*
 * CommandSystem.cpp
 *
 *  Created on: 29.08.2013
 *      Author: morgenro
 */

#include "CommandSystem.h"
#include "HostControl.h"
#include "Utils.h"
#include <ibrcommon/data/File.h>
#include <fstream>

namespace ctrl {

	CommandSystem::CommandSystem(CommandSet *parent)
	 : CommandSet(parent, "system")
	{
	}

	CommandSystem::~CommandSystem() {
	}

	bool CommandSystem::isCommand() const
	{
		return true;
	}

	void CommandSystem::execute(const std::string &parameters, std::iostream &stream) const
	{
		if (parameters.find("script") == 0) {
			// extract interpreter
			std::vector<std::string> params = Utils::tokenize(" ", parameters, 1);
			std::string shell = "/bin/sh";
			if (params.size() > 1) {
				shell = params[1];
			}

			// read and execute the given script
			std::string buffer;

			// open temporary file
			const ibrcommon::File path("/tmp");
			ibrcommon::TemporaryFile tmpfile(path, "script");
			std::fstream tmpout(tmpfile.getPath().c_str(), std::ios::out | std::ios::trunc);

			if (!tmpout.good()) {
				result_fail(stream);
				tmpfile.remove();
				return;
			}

			// send ack
			result(stream, 201, "CONTINUE (mark end with \".\")");

			// read script lines
			while (stream.good())
			{
				// get the next line
				getline(stream, buffer);

				// search for '\r\n' and remove the '\r'
				std::string::reverse_iterator iter = buffer.rbegin();
				if ( (*iter) == '\r' ) buffer = buffer.substr(0, buffer.length() - 1);

				// exit if "." was received
				if ("." == buffer) break;

				// write buffer to script file
				tmpout << buffer << std::endl;
			}

			// close the script file
			tmpout.close();

			result(stream, 212, "LISTING");

			// execute script
			HostControl::getInstance().system(shell + " " + tmpfile.getPath(), stream);

			// send ok
			result_ok(stream);

			// remove temporary file
			tmpfile.remove();
		}
		else if (parameters.find("shutdown") == 0)
		{
			// send ok
			result_ok(stream);

			// execute command
			HostControl::getInstance().shutdown();
		}
		else
		{
			result(stream, 212, "LISTING");

			// execute command in parameters
			HostControl::getInstance().system(parameters, stream);

			// send ok
			result_ok(stream);
		}
	}
} /* namespace ctrl */

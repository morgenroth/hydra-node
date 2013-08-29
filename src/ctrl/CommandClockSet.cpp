/*
 * CommandClockSet.cpp
 *
 *  Created on: 29.08.2013
 *      Author: morgenro
 */

#include "ctrl/CommandClockSet.h"
#include "ClockMonitor.h"
#include <unistd.h>
#include <sstream>

namespace ctrl {

	CommandClockSet::CommandClockSet(CommandSet *parent)
	 : CommandSet(parent, "set")
	{
	}

	CommandClockSet::~CommandClockSet()
	{
	}

	bool CommandClockSet::isCommand() const
	{
		return true;
	}

	void CommandClockSet::execute(const std::string &parameters, std::iostream &stream) const
	{
		std::stringstream ss(parameters);
		std::string keyword;
		ss >> keyword;

		if (keyword.find("frequency") == 0) {
			// read frequency
			ssize_t frequency = 0;
			ss >> frequency;

			ClockMonitor::getInstance().adjustFrequency(frequency);

			result_ok(stream);
		}
		else if (keyword.find("offset") == 0) {
			// read offset
			ssize_t offset = 0;
			ss >> offset;

			ClockMonitor::getInstance().adjustOffset(offset);

			result_ok(stream);
		}
		else {
			result_fail(stream);
		}
	}

} /* namespace ctrl */

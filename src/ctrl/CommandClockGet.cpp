/*
 * CommandClockGet.cpp
 *
 *  Created on: 29.08.2013
 *      Author: morgenro
 */

#include "ctrl/CommandClockGet.h"
#include "ClockMonitor.h"

namespace ctrl {

	CommandClockGet::CommandClockGet(CommandSet *parent)
	 : CommandSet(parent, "get")
	{
	}

	CommandClockGet::~CommandClockGet()
	{
	}

	bool CommandClockGet::isCommand() const
	{
		return true;
	}

	void CommandClockGet::execute(const std::string &parameters, std::iostream &stream) const
	{
		const ClockMonitor::ClockData &data = ClockMonitor::getInstance().getData();

		if (parameters.find("all") == 0) {
			result_listing(stream);
			stream << "Offset: " << data.offset << std::endl;
			stream << "Delay: " << data.delay << std::endl;
			stream << "Timex-offset: " << data.txc.offset << std::endl;
			stream << "Timex-freq: " << data.txc.freq << std::endl;
			stream << "Timex-tick: " << data.txc.tick << std::endl;
			result_done(stream);
		}
		else if (parameters.find("frequency") == 0) {
			result_value(stream);
			stream << data.txc.freq << std::endl;
			result_done(stream);
		}
		else if (parameters.find("offset") == 0) {
			result_value(stream);
			stream << data.txc.offset << std::endl;
			result_done(stream);
		}
		else {
			result_fail(stream);
		}
	}

} /* namespace ctrl */

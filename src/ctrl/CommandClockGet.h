/*
 * CommandClockGet.h
 *
 *  Created on: 29.08.2013
 *      Author: morgenro
 */

#ifndef COMMANDCLOCKGET_H_
#define COMMANDCLOCKGET_H_

#include "ctrl/CommandSet.h"

namespace ctrl {

	class CommandClockGet : public CommandSet {
	public:
		CommandClockGet(CommandSet *parent);
		virtual ~CommandClockGet();

		virtual bool isCommand() const;

		virtual void execute(const std::string &parameters, std::iostream &stream) const;
	};

} /* namespace ctrl */
#endif /* COMMANDCLOCKGET_H_ */

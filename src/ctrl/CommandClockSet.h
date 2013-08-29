/*
 * CommandClockSet.h
 *
 *  Created on: 29.08.2013
 *      Author: morgenro
 */

#ifndef COMMANDCLOCKSET_H_
#define COMMANDCLOCKSET_H_

#include "ctrl/CommandSet.h"

namespace ctrl {

	class CommandClockSet : public CommandSet {
	public:
		CommandClockSet(CommandSet *parent);
		virtual ~CommandClockSet();

		virtual bool isCommand() const;

		virtual void execute(const std::string &parameters, std::iostream &stream) const;
	};

} /* namespace ctrl */
#endif /* COMMANDCLOCKSET_H_ */

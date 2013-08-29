/*
 * CommandSystem.h
 *
 *  Created on: 29.08.2013
 *      Author: morgenro
 */

#ifndef COMMANDSYSTEM_H_
#define COMMANDSYSTEM_H_

#include "ctrl/CommandSet.h"

namespace ctrl {

	class CommandSystem : public CommandSet {
	public:
		CommandSystem(CommandSet *parent);
		virtual ~CommandSystem();

		virtual bool isCommand() const;

		virtual void execute(const std::string &parameters, std::iostream &stream) const;
	};

} /* namespace ctrl */
#endif /* COMMANDSYSTEM_H_ */

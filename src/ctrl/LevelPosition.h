/*
 * LevelPosition.h
 *
 *  Created on: 29.08.2013
 *      Author: morgenro
 */

#ifndef LEVELPOSITION_H_
#define LEVELPOSITION_H_

#include "ctrl/CommandSet.h"

namespace ctrl {

	class LevelPosition : public CommandSet {
	public:
		LevelPosition(CommandSet *parent);
		virtual ~LevelPosition();

		virtual bool isCommand() const;

		virtual void execute(const std::string &parameters, std::iostream &stream) const;
	};

} /* namespace ctrl */
#endif /* LEVELPOSITION_H_ */

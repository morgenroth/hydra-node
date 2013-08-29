/*
 * LevelStats.h
 *
 *  Created on: 29.08.2013
 *      Author: morgenro
 */

#ifndef LEVELSTATS_H_
#define LEVELSTATS_H_

#include "ctrl/CommandSet.h"

namespace ctrl {

	class LevelStats : public CommandSet {
	public:
		LevelStats(CommandSet *parent);
		virtual ~LevelStats();

		virtual bool isCommand() const;

		virtual void execute(const std::string &parameters, std::iostream &stream) const;
	};

} /* namespace ctrl */
#endif /* LEVELSTATS_H_ */

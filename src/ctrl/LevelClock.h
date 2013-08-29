/*
 * LevelClock.h
 *
 *  Created on: 29.08.2013
 *      Author: morgenro
 */

#ifndef LEVELCLOCK_H_
#define LEVELCLOCK_H_

#include "ctrl/CommandSet.h"

namespace ctrl {

	class LevelClock : public CommandSet {
	public:
		LevelClock(CommandSet *parent);
		virtual ~LevelClock();
	};

} /* namespace ctrl */
#endif /* LEVELCLOCK_H_ */

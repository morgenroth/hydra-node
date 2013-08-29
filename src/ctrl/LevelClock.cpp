/*
 * LevelClock.cpp
 *
 *  Created on: 29.08.2013
 *      Author: morgenro
 */

#include "ctrl/LevelClock.h"
#include "ctrl/CommandClockGet.h"
#include "ctrl/CommandClockSet.h"

namespace ctrl {

	LevelClock::LevelClock(CommandSet *parent)
	 : CommandSet(parent, "clock")
	{
		CommandSet::add(new CommandClockGet(this));
		CommandSet::add(new CommandClockSet(this));
	}

	LevelClock::~LevelClock()
	{
	}

} /* namespace ctrl */

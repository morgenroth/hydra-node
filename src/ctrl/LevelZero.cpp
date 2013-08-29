/*
 * LevelZero.cpp
 *
 *  Created on: 29.08.2013
 *      Author: morgenro
 */

#include "ctrl/LevelZero.h"
#include "ctrl/LevelPosition.h"
#include "ctrl/LevelClock.h"
#include "ctrl/LevelStats.h"
#include "ctrl/CommandSystem.h"

namespace ctrl {

	LevelZero::LevelZero() : CommandSet(0, "zero") {
		CommandSet::add(new LevelPosition(this));
		CommandSet::add(new LevelClock(this));
		CommandSet::add(new LevelStats(this));
		CommandSet::add(new CommandSystem(this));
	}

	LevelZero::~LevelZero() {
	}

	CommandSet* LevelZero::getInstance()
	{
		static CommandSet *entry = NULL;
		if (entry == NULL) {
			entry = new LevelZero();
		}
		return entry;
	}

} /* namespace ctrl */

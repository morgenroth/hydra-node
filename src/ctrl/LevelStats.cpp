/*
 * LevelStats.cpp
 *
 *  Created on: 29.08.2013
 *      Author: morgenro
 */

#include "ctrl/LevelStats.h"

namespace ctrl {

	LevelStats::LevelStats(CommandSet *parent)
	 : CommandSet(parent, "stats")
	{
	}

	LevelStats::~LevelStats()
	{
	}

} /* namespace ctrl */

/*
 * LevelDtnd.h
 *
 *  Created on: 29.08.2013
 *      Author: morgenro
 */

#ifndef LEVELDTND_H_
#define LEVELDTND_H_

#include "ctrl/CommandSet.h"

namespace ctrl {

	class LevelDtnd : public CommandSet {
	public:
		LevelDtnd(CommandSet *parent);
		virtual ~LevelDtnd();
	};

} /* namespace ctrl */
#endif /* LEVELDTND_H_ */

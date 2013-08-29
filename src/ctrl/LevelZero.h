/*
 * LevelZero.h
 *
 *  Created on: 29.08.2013
 *      Author: morgenro
 */

#ifndef LEVELZERO_H_
#define LEVELZERO_H_

#include "ctrl/CommandSet.h"

namespace ctrl {

	class LevelZero : public CommandSet {
	public:
		LevelZero();
		virtual ~LevelZero();

		static CommandSet* getInstance();
	};

} /* namespace ctrl */
#endif /* LEVELZERO_H_ */

/*
 * LevelPosition.cpp
 *
 *  Created on: 29.08.2013
 *      Author: morgenro
 */

#include "ctrl/LevelPosition.h"
#include "FakeGPS.h"
#include <sstream>

namespace ctrl {

	LevelPosition::LevelPosition(CommandSet *parent)
	 : CommandSet(parent, "position")
	{
	}

	LevelPosition::~LevelPosition() {
	}

	bool LevelPosition::isCommand() const
	{
		return true;
	}

	void LevelPosition::execute(const std::string &parameters, std::iostream &stream) const
	{
		std::stringstream ss(parameters);
		std::string keyword;
		ss >> keyword;

		if (keyword.find("disable") == 0) {
			FakeGPS::getInstance().disable();
			result_ok(stream);
		}
		else if (keyword.find("enable") == 0) {
			FakeGPS::getInstance().setState(FakeGPS::GPS_STATE_INITIAL);
			result_ok(stream);
		}
		else if (keyword.find("state") == 0) {
			result_value(stream);
			stream << FakeGPS::getInstance().getState() << std::endl;
			result_done(stream);
		}
		else if (keyword.find("get") == 0) {
			float x = 0.0f;
			float y = 0.0f;
			float z = 0.0f;

			FakeGPS::getInstance().getPosition(x, y, z);

			result_listing(stream);

			stream << "state: " << FakeGPS::getInstance().getState() << std::endl;
			stream << "x: " << x << std::endl;
			stream << "y: " << y << std::endl;
			stream << "z: " << z << std::endl;

			result_done(stream);
		}
		else if (keyword.find("set") == 0) {
			float x = 0.0f;
			float y = 0.0f;
			float z = 0.0f;

			ss >> x >> y >> z;

			FakeGPS::getInstance().setPosition(x, y, z);
			result_ok(stream);
		}
		else {
			result_fail(stream);
		}
	}

} /* namespace ctrl */

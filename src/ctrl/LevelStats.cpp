/*
 * LevelStats.cpp
 *
 *  Created on: 29.08.2013
 *      Author: morgenro
 */

#include "ctrl/LevelStats.h"
#include "Utils.h"
#include <ibrcommon/data/File.h>
#include <sstream>

namespace ctrl {

	LevelStats::LevelStats(CommandSet *parent)
	 : CommandSet(parent, "stats")
	{
	}

	LevelStats::~LevelStats()
	{
	}

	bool LevelStats::isCommand() const
	{
		return true;
	}

	void LevelStats::execute(const std::string &parameters, std::iostream &stream) const
	{
		std::stringstream ss(parameters);
		std::string keyword;
		ss >> keyword;

		if (keyword.find("interfaces") == 0) {
			result_listing(stream);

			const ibrcommon::File interfaces_path("/sys/class/net");

			if (interfaces_path.isDirectory()) {
				std::list<ibrcommon::File> interfaces;
				interfaces_path.getFiles(interfaces);

				for (std::list<ibrcommon::File>::const_iterator it = interfaces.begin(); it != interfaces.end(); ++it)
				{
					if ((*it).isSystem()) continue;

					stream << (*it).getBasename() <<
							" rx:" << Utils::readSysFile((*it).getPath() + "/statistics/rx_bytes") <<
							" tx:" << Utils::readSysFile((*it).getPath() + "/statistics/tx_bytes") << std::endl;
				}
			}

			result_done(stream);
		}
		else {
			result_fail(stream);
		}
	}

} /* namespace ctrl */

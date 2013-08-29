/*
 * ClockMonitor.cpp
 *
 *  Created on: 27.08.2013
 *      Author: morgenro
 */

#include "ClockMonitor.h"
#include <ibrcommon/appstreambuf.h>
#include <sstream>
#include <iostream>
#include <unistd.h>

ClockMonitor& ClockMonitor::getInstance()
{
	static ClockMonitor instance;
	return instance;
}

ClockMonitor::ClockMonitor()
 : _reference_host(), _running(true)
{
}

ClockMonitor::~ClockMonitor() {
}

void ClockMonitor::setReference(const std::string &reference_host)
{
	_reference_host = reference_host;
}

void ClockMonitor::adjustOffset(size_t offset)
{
	// set timex data
	struct timex txc;
	txc.modes = ADJ_OFFSET;
	txc.offset = offset;

	if (::adjtimex(&txc) >= 0) {
		// success
	}
}

void ClockMonitor::adjustFrequency(size_t frequency)
{
	// set timex data
	struct timex txc;
	txc.modes = ADJ_FREQUENCY;
	txc.freq = frequency;

	if (::adjtimex(&txc) >= 0) {
		// success
	}
}

const ClockMonitor::ClockData& ClockMonitor::getData() const
{
	return _data;
}

void ClockMonitor::setup() throw () {
}

void ClockMonitor::run() throw () {
	while (_running) {
		// measure clock offset and collect data
		measure(_data);

		//std::cout << _data << std::endl;

		// wait for 30 seconds
		for (int i = 0; i < 300; i++) {
			Thread::sleep(100);
		}
	}
}

void ClockMonitor::__cancellation() throw () {
	_running = true;
}

void ClockMonitor::finally() throw () {
}

void ClockMonitor::measure(ClockMonitor::ClockData &data) const {
	// measure time offset if a reference host is set
	if (_reference_host.length() > 0) {
		std::stringstream cmd;
		cmd << "ntpdate -q " << _reference_host << std::endl;

		ibrcommon::appstreambuf app(cmd.str(), ibrcommon::appstreambuf::MODE_READ);
		std::istream stream(&app);

		std::string keyword;

		while (stream.good()) {
			stream >> keyword;
			if (keyword == "offset") {
				stream >> data.offset;
			}
			else if (keyword == "delay") {
				stream >> data.delay;
			}
		}
	}

	// get timex data
	if (::adjtimex(&data.txc) >= 0) {
		// data valid
	}
}

std::ostream& operator<<(std::ostream &stream, const ClockMonitor::ClockData &data)
{
	stream << "[" << data.txc.time.tv_sec << "." << data.txc.time.tv_usec << "] offset: " << data.offset << ", delay: " << data.delay;
	stream << ", timex-offset: " << data.txc.offset << ", timex-freq: " << data.txc.freq << ", timex-tick: " << data.txc.tick;
	return stream;
}

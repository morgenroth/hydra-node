/*
 * FakeGPS.cpp
 *
 *  Created on: 17.01.2011
 *      Author: morgenro
 */

#include "FakeGPS.h"
#include <iostream>

FakeGPS& FakeGPS::getInstance()
{
	static FakeGPS gps;
	return gps;
}

FakeGPS::FakeGPS()
 : _state(GPS_STATE_INITIAL), _lon(0), _lat(0), _alt(0)
{
}

FakeGPS::~FakeGPS()
{
}

FakeGPS::GPS_STATE FakeGPS::getState() const
{
	return _state;
}

void FakeGPS::disable()
{
	_state = GPS_STATE_DISABLED;
	_lon = 0.0;
	_lat = 0.0;
	_alt = 0.0;
}

void FakeGPS::setState(GPS_STATE state)
{
	_state = state;
}

void FakeGPS::getPosition(float &lon, float &lat) const
{
	if (_state == GPS_STATE_DISABLED) return;

	lon = _lon;
	lat = _lat;
}

void FakeGPS::getPosition(float &lon, float &lat, float &alt) const
{
	if (_state == GPS_STATE_DISABLED) return;

	lon = _lon;
	lat = _lat;
	alt = _alt;
}

void FakeGPS::setPosition(const float &lon, const float &lat, const float &alt)
{
	if (_state == GPS_STATE_DISABLED) return;

	_state = GPS_STATE_GOT_FIX;
	_lon = lon;
	_lat = lat;
	_alt = alt;
}

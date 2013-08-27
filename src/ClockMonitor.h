/*
 * ClockMonitor.h
 *
 *  Created on: 27.08.2013
 *      Author: morgenro
 */

#ifndef CLOCKMONITOR_H_
#define CLOCKMONITOR_H_

#include <ibrcommon/thread/Thread.h>
#include <string>
#include <sys/time.h>
#include <sys/timex.h>
#include <iostream>

class ClockMonitor : public ibrcommon::JoinableThread {
	public:
		static ClockMonitor& getInstance();

		virtual ~ClockMonitor();

		void setReference(const std::string &reference_host);

		void adjustOffset(size_t offset);
		void adjustFrequency(size_t frequency);

		class ClockData {
		public:
			double offset;
			double delay;
			struct timex txc;

			friend
			std::ostream& operator<<(std::ostream &stream, const ClockData &data);
		};

		const ClockData& getData() const;

	protected:
		ClockMonitor();

		void setup() throw ();
		void run() throw ();
		void __cancellation() throw ();
		void finally() throw ();

	private:
		void measure(ClockData &data) const;

		std::string _reference_host;
		bool _running;
		ClockData _data;
};

#endif /* CLOCKMONITOR_H_ */

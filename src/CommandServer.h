/*
 * CommandServer.h
 *
 *  Created on: 14.01.2011
 *      Author: morgenro
 */

#ifndef COMMANDSERVER_H_
#define COMMANDSERVER_H_

#include <ibrcommon/net/vinterface.h>
#include <ibrcommon/net/socket.h>
#include <ibrcommon/net/socketstream.h>
#include <ibrcommon/thread/Thread.h>
#include <ibrcommon/thread/Mutex.h>
#include <sstream>

class CommandServer : public ibrcommon::JoinableThread
{
public:
	CommandServer(unsigned int port = 3486);
	virtual ~CommandServer();

	void setup() throw ();
	void run() throw ();
	void finally() throw ();

	void __cancellation() throw ();

private:
	class Message
	{
	public:
		enum MSG_TYPE
		{
			MSG_UNKNOWN = 0,
			MSG_SCRIPT = 1,
			MSG_GPS_POSITION = 2,
			MSG_SHUTDOWN = 3
		} _type;

		Message(const MSG_TYPE type = MSG_UNKNOWN);
		virtual ~Message();

		float _float_values[3];
		std::stringstream _data;
	};

	class Connection : public ibrcommon::DetachedThread
	{
	public:
		Connection(ibrcommon::clientsocket *sock, ibrcommon::Conditional &m, unsigned int &c);
		virtual ~Connection();

		void setup() throw ();
		void run() throw ();
		void finally() throw ();

		void __cancellation() throw ();

	private:
		ibrcommon::socketstream _stream;

		ibrcommon::Conditional &_active_connections_cond;
		unsigned int &_active_connections;
	};

	friend class Connection;

	friend
	std::ostream& operator<<(std::ostream&, const Message &msg);

	friend
	std::istream& operator>>(std::istream&, Message &msg);

	ibrcommon::tcpserversocket _srv;
	bool _running;

	ibrcommon::Conditional _active_connections_cond;
	unsigned int _active_connections;
};

#endif /* COMMANDSERVER_H_ */

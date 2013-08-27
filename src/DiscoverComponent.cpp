/*
 * DiscoverComponent.cpp
 *
 *  Created on: 14.01.2011
 *      Author: morgenro
 */

#include "DiscoverComponent.h"
#include <netinet/in.h>
#include <sstream>

DiscoverComponent::Message::Message(const DiscoverComponent::Message::MSG_TYPE type)
 : _type(type), _hostname()
{
}

DiscoverComponent::Message::~Message()
{

}

std::ostream& operator<<(std::ostream &stream, const DiscoverComponent::Message &msg)
{
	stream.write((char*)&msg._type, 1);

	switch (msg._type)
	{
		case DiscoverComponent::Message::MSG_HELLO:
		{
			stream << "HELLO" << std::flush;
			break;
		}

		case DiscoverComponent::Message::MSG_NODE:
		{
			uint32_t len_of_name = htonl(msg._hostname.length());
			stream.write((char*)&len_of_name, 4);
			stream << msg._hostname;
			break;
		}
	}

	return stream;
}

std::istream& operator>>(std::istream &stream, DiscoverComponent::Message &msg)
{
	char type = 0;
	stream.read(&type, 1);
	msg._type = (DiscoverComponent::Message::MSG_TYPE)type;

	switch (msg._type)
	{
		case DiscoverComponent::Message::MSG_HELLO:
		{
			break;
		}

		case DiscoverComponent::Message::MSG_NODE:
		{
			break;
		}
	}

	return stream;
}

DiscoverComponent::DiscoverComponent(const std::string &hostname, unsigned int port, const ibrcommon::vinterface &iface)
 : _vaddress("225.16.16.1", port), _hostname(hostname)
{
	ibrcommon::multicastsocket *mcast = new ibrcommon::multicastsocket(port);
	_vsock.add( mcast );
	_vsock.up();
	mcast->join(_vaddress, iface);
}

DiscoverComponent::~DiscoverComponent()
{
	_vsock.destroy();
}

void DiscoverComponent::run()
{
	char data[1500];

	while (true)
	{
		ibrcommon::socketset fds;
		_vsock.select(&fds, NULL, NULL, NULL);

		for (ibrcommon::socketset::const_iterator iter = fds.begin(); iter != fds.end(); iter++)
		{
			// socket to read
			ibrcommon::udpsocket &s = dynamic_cast<ibrcommon::udpsocket&>(**iter);

			ibrcommon::vaddress client_addr;

			// data waiting
			int len = s.recvfrom(data, 1500, MSG_WAITALL, client_addr);

			std::stringstream ss; ss.write(data, len);

			Message m;
			ss >> m;

			// response to any HELLO
			if (m._type == Message::MSG_HELLO)
			{
				std::cout << "HELLO received" << std::endl;

				Message reply(Message::MSG_NODE);
				reply._hostname = _hostname;

				std::stringstream ss; ss << reply;
				std::string reply_data = ss.str();

				s.sendto(reply_data.c_str(), reply_data.length(), 0, client_addr);
			}
		}
	}
}

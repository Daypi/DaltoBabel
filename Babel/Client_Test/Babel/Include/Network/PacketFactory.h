#pragma once

#include			<queue>
#include			"Packet.h"
#include			"CircularBuffer.hpp"

class								PacketFactory
{
	static const unsigned int		BUFF_SIZE = 65025;

	std::queue<Packet *>			_packet;
	CircularBuffer					_buff;
	Packet							*_current;

public:
	PacketFactory();
	~PacketFactory();

	void							feed(const char *, unsigned int);
	Packet							*getPacket();
};
#pragma once

#include			<queue>
#include			"Packet.h"
#include			"CircularBuffer.hpp"

class								PacketFactory
{
	std::queue<Packet *>			_packet;
	CircularBuffer					_buff;
	Packet							*_current;

public:
	PacketFactory();
	~PacketFactory();

	void							feed(const char *, unsigned int);
	Packet							*getPacket();
};
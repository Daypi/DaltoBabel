#include	<iostream>
#include	"Include/Network/PacketFactory.h"

PacketFactory::PacketFactory()
{
	this->_current = 0;
}

PacketFactory::~PacketFactory()
{
}

void			PacketFactory::feed(const char *data, unsigned int size)
{
	char		header[Packet::HEADER_SIZE];
	char		*packet;
	bool		cont = true;

	this->_buff.write(data, size);
	while (cont)
	{
		if (this->_buff.getReadable() >= Packet::HEADER_SIZE)
		{
			if (this->_current == 0)
				this->_current = new Packet();
			this->_buff.readNoModify(header, Packet::HEADER_SIZE);
			this->_current->header(header);
			if (this->_current->size() <= (unsigned int)this->_buff.getReadable())
			{
				packet = new char[this->_current->size()];
				this->_buff.read(packet, this->_current->size());
				this->_current->deserialize(packet);
                delete[] packet;
				this->_packet.push(this->_current);
				this->_current = 0;
				cont = true;
				continue;
			}
			cont = false;
		}
		cont = false;
	}
}

Packet			*PacketFactory::getPacket()
{
	Packet		*packet;

	if (this->_packet.empty())
		return (0);
	packet = this->_packet.front();
	this->_packet.pop();
	std::cout << this->_buff.getReadable() << std::endl;
	return (packet);
}

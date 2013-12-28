#include		<iostream>
#include		"Server.h"
#include		"Util.hpp"

int				main()
{
	try
	{
		Server	server(11235, 5);

		server.start();
	}
	catch (const Exception& e)
	{
		std::cout << e.what();
		std::cin.get();
	}
	/*Packet			packet;
	Packet			packet2;
	Packet			packet3;
	PacketFactory	factory;
	unsigned short	size;
	std::string		format;
	unsigned short	i;
	Packet			*tmp;
	unsigned char	*str;

	packet.setRequestUID(0);
	packet.setInstruction(3);
	packet.setFormat("cs");
	packet.updateData(7);
	packet.appendToData<char>(0, 1);
	packet.appendToData(1, "");

	packet2.setRequestUID(0);
	packet2.setInstruction(4);
	packet2.setFormat("cc");
	packet2.updateData(6);
	packet2.appendToData<char>(0, 1);
	packet2.appendToData<char>(1, 0);

	packet3.setRequestUID(0);
	packet3.setInstruction(0);
	packet3.setFormat("clssc");
	packet3.updateData(39);
	packet3.appendToData<char>(0, 1);
	packet3.appendToData<short>(1, 2);
	packet3.appendToData(2, "pouet");
	packet3.appendToData(3, "");
	packet3.appendToData<char>(4, 3);
	packet3.appendToData(5, "prout");
	packet3.appendToData(6, "");
	packet3.appendToData<char>(7, 3);

	char		*tab = new char[packet.size() + packet2.size() + packet3.size()];

	LibC::memcpy(tab, packet.serialize(), packet.size());
	LibC::memcpy(tab + packet.size(), packet2.serialize(), packet2.size());
	LibC::memcpy(tab + packet.size() + packet2.size(), packet3.serialize(), packet3.size());
	factory.feed(tab, packet.size() + packet2.size() + packet3.size());

	while ((tmp = factory.getPacket()))
	{
		tmp->show();
		tmp->show();
	}
	delete[] tab;*/
	std::cin.get();
	return (0);
}
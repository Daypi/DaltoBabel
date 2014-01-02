#include		<iostream>
#include		"Server.h"
#include		"Util.hpp"
#include		"Folder.h"

int				main()
{
	/*AccountManager	manager;

	manager.create("192.168.0.33", "Titi", "password");
	manager.create("127.0.0.1", "Jeanjean", "toto");
	manager.addContact("Jeanjean", "Titi");
	manager.save();
	manager.show();
	manager.clear();
	std::cout << manager.size() << std::endl;
	manager.show();
	manager.load();
	std::cout << manager.size() << std::endl;
	manager.show();
	std::cin.get();*/
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
	packet.updateData(11);
	packet.appendToData<char>(0, 1);
	packet.appendToData(1, "toto");

	packet2.setRequestUID(0);
	packet2.setInstruction(4);
	packet2.setFormat("cc");
	packet2.updateData(6);
	packet2.appendToData<char>(0, 1);
	packet2.appendToData<char>(1, 0);

	packet3.setRequestUID(0);
	packet3.setInstruction(0);
	packet3.setFormat("css");
	packet3.updateData(20);
	packet3.appendToData<char>(0, 1);
	packet3.appendToData(1, "prout");
	packet3.appendToData(2, "toto");

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
	delete[] tab;
	std::cin.get();*/
	return (0);
}

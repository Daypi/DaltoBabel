#include		<iostream>
#include		"Server.h"
#include		"Util.hpp"

int				main()
{
	/*try
	{
		Server	server(11235, 5);

		server.start();
	}
	catch (Exception& e)
	{
		std::cout << e.what();
		std::cin.get();
	}*/
	Packet			packet;
	Packet			packet2;
	Packet			packet3;
	PacketFactory	factory;
	unsigned short	size;
	std::string		format;
	unsigned short	i;
	Packet			*tmp;
	unsigned char	*str;

	/*packet.setRequestUID(42);
	packet.setInstruction(42);
	packet.updateData(118);
	packet.appendToData(0, "salut");
	packet.appendToData(1, "coucou");
	packet.appendToData<char>(2, 42);
	packet.appendToData(3, "couc");
	packet.appendToData<char>(4, 43);
	packet.appendToData<char>(5, 44);
	packet.appendToData<char>(6, 45);
	packet.appendToData(7, "lol");
	packet.appendToData(8, "prout");
	packet.appendToData(9, "zizi");
	packet.appendToData<char>(10, 'A');
	packet.appendToData<short>(11, 4);
	packet.appendToData(12, "zizi1");
	packet.appendToData<char>(13, '1');
	packet.appendToData(14, "zizi2");
	packet.appendToData<char>(15, '2');
	packet.appendToData(16, "zizi3");
	packet.appendToData<char>(17, '3');
	packet.appendToData(18, "zizi4");
	packet.appendToData<char>(19, '4');

	packet.setFormat("sscscccsssclsc");

	str = (unsigned char *)packet.serialize();
	for (unsigned int i = 0; i < packet.size(); ++i)
	{
		std::cout << Util::format<const std::string&>('0', 2, Util::toHex<unsigned int>(str[i])) << " ";
	}
	std::cout << std::endl;
	
	packet2.setRequestUID(21);
	packet2.setInstruction(84);
	packet2.updateData(13);
	packet2.appendToData<char>(0, '*');
	packet2.appendToData(1, "coucou");

	packet2.setFormat("cs");*/

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
	packet3.updateData(7);
	packet3.appendToData<char>(0, 1);
	packet3.appendToData<short>(1, 0);

	char		*tab = new char[packet.size() + packet2.size() + packet3.size()];

	LibC::memcpy(tab, packet.serialize(), packet.size());
	LibC::memcpy(tab + packet.size(), packet2.serialize(), packet2.size());
	LibC::memcpy(tab + packet.size() + packet2.size(), packet3.serialize(), packet3.size());
	factory.feed(tab, packet.size() + packet2.size() + packet3.size());

	while ((tmp = factory.getPacket()))
	{
		tmp->show();
	}
	delete[] tab;
	std::cin.get();
	return (0);
}
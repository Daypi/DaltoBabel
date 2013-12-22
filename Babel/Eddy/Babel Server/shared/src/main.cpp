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
	catch (Exception& e)
	{
		std::cout << e.what();
		std::cin.get();
	}
	/*Packet			packet;
	PacketFactory	factory;
	unsigned short	size;
	std::string		format;
	unsigned short	i;
	Packet			*tmp;
	unsigned char	*str;

	packet.setRequestUID(42);
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
	
	factory.feed(packet.serialize(), packet.size());

	tmp = factory.getPacket();
	if (tmp)
	{
		tmp->show();
	}
	*/
	std::cin.get();
	return (0);
}
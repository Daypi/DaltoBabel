#include		<iostream>
#include		"Server.h"

int				main()
{
	try
	{
		Server	server(1337, 5);

		server.start();
	}
	catch (Exception& e)
	{
		std::cout << e.what();
		std::cin.get();
	}
	/*Packet			packet;
	unsigned short	size;
	std::string		format;
	unsigned short	i;

	packet.setRequestUID(42);
	packet.setInstruction(42);
	packet.setDataSize(42);
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

	packet.show();
	*/
	std::cin.get();
	return (0);
}
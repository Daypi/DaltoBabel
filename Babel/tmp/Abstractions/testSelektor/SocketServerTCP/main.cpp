#include	<stdio.h>
#include	"SocketServerTCP.h"
#include	"SocketServerUDP.h"
#include	"SocketClientTCP.h"
#include	"SocketClientUDP.h"

int		main(void)
{
//	SocketClientUDP	sock;
	/*SocketClientTCP	sock;
	char			buffer[4096];
	int				bytesRec;
	int				i = 0;

	try
	{
		sock.init(1337, "127.0.0.1");
		std::cout << "INIT" << std::endl;
	}
	catch (Exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	while (42)
	{
		if (sock.isWritable())
		{
			char	toto[40];
			++i;
			std::cout << "sending : ";
			sprintf(toto, "%d ", i);
			try
			{
				sock.send(toto, strlen(toto));
			}
			catch (Exception &e)
			{
				std::cout << e.what() << std::endl;
			}
			std::cout << "sended: ";
		}
		if (sock.isReadable())
		{
			try
			{
				bytesRec = 0;
				std::cout << "reeding : ";
				sock.recv(buffer, 4098, &bytesRec);
				std::cout << buffer << "| size readed = " << bytesRec << std::endl;
			}
			catch (Exception &e)
			{
				std::cout << "server disconnected." << std::endl;
			}
		}
		std::cout << "loop : " << sock.isReadable() << std::endl;
		Sleep(1000);
	}
	sock.close();
	return (0);*/





	//SAMPLE USING SERVERTCP



	// SocketServerTCP	sock;
	//std::map<unsigned int, std::pair<const char *, int>> tmp;
	//bool toto = false;
	//unsigned int uid_client = 0;
	//try
	//{
	//	sock.init(1337, 42);
	//}
	//catch (Exception &e)
	//{
	//	std::cout << e.what() << std::endl;
	//}
	//std::cout << "INIT" << std::endl;
	//while (42)
	// {
	//	 if (sock.isReadable(0).size() == 1)
	//	 {
	//		 std::cout << "Client is connecting" << std::endl;
	//		 sock.checkConnection();
	//		 toto = true;
	//		 ++uid_client;
	//		 std::cout << "connected" << std::endl;
	//	 }
	//	 if ((toto) && (sock.isReadable(uid_client).size() == 1))
	//	 {
	//		 tmp = sock.recv(uid_client, 2048);
	//		 if (tmp.size() != 1)
	//		 {
	//			 std::cout << "problem plus de client" << std::endl;
	//			 toto = false;
	//		 }
	//		 else
	//		 {
	//			 std::cout << "recv = " << tmp[uid_client].first << std::endl;
	//			 try
	//			 {
	//				 if (sock.isWritable(uid_client).size() == 1)
	//					 sock.send(uid_client, "Hello World!!!", 14);
	//				 std::cout << "send" << std::endl;
	//			 }
	//			 catch (Exception &ex)
	//			 {
	//				 std::cout << "send failed client disconnected. = " << ex.what() << std::endl;
	//			}

	//		 }
	//	 }
	// }
	// sock.closeServer();
	// return (0);


	//SAMPLE USING SERVERUDP

	std::map<unsigned int, std::pair<const char *, int>> tmp;
	std::map<unsigned int, std::pair<const char *, int>>::iterator it;
	SocketServerUDP	sock;
	try
	{
		sock.init(1337);
		std::cout << "INIT" << std::endl;
	}
	catch (Exception &e)
	{
		std::cout << e.what() << std::endl;
	}
		 while (42)
		 {
			 if (sock.isIAmReadable())
			 {
				 try
				 {
					 tmp = sock.recv(2048);
				 }
				 catch (Exception &ex)
				 {
					 std::cout << "client disconnected" << std::endl;
					 tmp.clear();
				 }
				 if (tmp.size() == 1)
				 {
					 for (it = tmp.begin(); it != tmp.end(); ++it)
						 std::cout << "recv = " << it->second.first << std::endl;
					 if (sock.isWritable().size() != 0)
					 {
						 for (it = tmp.begin(); it != tmp.end(); ++it)
						 {
							 sock.send(it->first, "hello world!!!", 14);
							 std::cout << "send" << std::endl;
						 }
					 }
				 }
			 }
	
		 }
	sock.closeServer();

	return (0);
}
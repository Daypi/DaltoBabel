//
// TexturesController.hpp for rtype in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Tue Oct 29 09:27:15 2013 martin lequeux-gruninger
// Last update Wed Nov 20 16:27:28 2013 martin lequeux-gruninger
//

#pragma		once

#include	<iostream>
#include	<SFML/System.hpp>
#include	<SFML/Graphics.hpp>
#include	<queue>
#include	"SocketClientTCP.h"
#include	"SocketClientUDP.h"
#include	"PacketFactory.h"
#include    "Controller/Display.hh"

namespace	RType
{
  namespace Controller
  {
    class		Controller;
  }
}

namespace	RType
{
  namespace Controller
  {
    class		Network
    {
      std::queue<Packet *>	_sendQueueUDP;
      std::queue<Packet *>	_sendQueueTCP;
      SocketClientUDP		*_sockUDP;
      SocketClientTCP		*_sockTCP;
      PacketFactory		_factory;
      bool			_init;
      Controller		*_controller;
	  int			_reqUID;

    private:
      Network		&operator=(const Network &);
      Network(const Network &);

    public:
      Network(Controller *controller)
      {
	_controller = controller;
	_sockUDP = NULL;
	_sockTCP = NULL;
	_init = false;
	_reqUID = 0;
      }

      ~Network() {}

	  void	connect(const std::string &ip, int port);
	  void	setInit(bool b);
	  void	handleNetworkUDP();
	  void	handleNetworkTCP();

	  void	handlePackets()
      {
	Packet *packet;

	while ((packet = this->_factory.getPacket()))
	  {
		  if (packet->getGroup() == 0 && packet->getInstruction() == 0)
			  this->getLogin(packet);
		  else if (packet->getGroup() == 0 && packet->getInstruction() == 1)
			  this->getMsgChat(packet);
		  else if (packet->getGroup() == 0 && packet->getInstruction() == 3)
			  this->getRooms(packet);
		  else if (packet->getGroup() == 0 && packet->getInstruction() == 4)
			  this->getLevels(packet);
		  else if (packet->getGroup() == 1 && packet->getInstruction() == 0)
			  return;
		  else if (packet->getGroup() == 1 && packet->getInstruction() == 1)
			  this->joinRoom(packet);
		  else if (packet->getGroup() == 1 && packet->getInstruction() == 2)
			  this->start(packet);
		  else if (packet->getGroup() == 1 && packet->getInstruction() == 3)
			  this->end(packet);
		  else if (packet->getGroup() == 1 && packet->getInstruction() == 5)
			  this->chatRoom(packet);
		  else if (packet->getGroup() == 1 && packet->getInstruction() == 6)
			  this->listLogins(packet);
		  else
		  {
			  std::cout << "PACKET NON GERE" << std::endl;
			  packet->show();
		  }
	  }
      }

      void	handleNetwork()
      {
		if (_init)
		{
			handleNetworkUDP();
			handleNetworkTCP();
			handlePackets();
		}
      }

	  void	pushUDP(Packet *packet)
	  {
		  this->_sendQueueUDP.push(packet);
	  }

	  void	pushTCP(Packet *packet)
	  {
		  this->_sendQueueTCP.push(packet);
	  }

	  int	getUID()
	  {
		  return _reqUID++;
	  }

	  void	getLogin(Packet *packet);
	  void	getRooms(Packet *packet);
	  void	getMsgChat(Packet *packet);
	  void	getLevels(Packet *packet);
	  void	joinRoom(Packet *packet);
	  void	start(Packet *packet);
	  void	end(Packet *packet);
	  void	chatRoom(Packet *packet);
	  void	listLogins(Packet *packet);
	};
  }
}

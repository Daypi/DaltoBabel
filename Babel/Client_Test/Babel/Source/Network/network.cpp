#include "Include/Network/network.h"

Network::Network()
{
    _sockUDP = NULL;
    _sockTCP = NULL;
    _init = false;
    _reqUID = 0;
}

Network::~Network()
{
}

void	Network::setInit(bool b)
{
    _init = b;
}

void	Network::connect(const std::string &ip, int port)
{
    if (_init == false)
    {
        this->_sockUDP = new SocketClientUDP;

        try
        {
            this->_sockUDP->init(port, ip.c_str());
        }
        catch (Exception &e)
        {
            delete _sockUDP;
            _sockUDP = NULL;
            _init = false;
            throw Exception(e);
        }
        this->_sockTCP = new SocketClientTCP;
        try
        {
            this->_sockTCP->init(port, ip.c_str());
        }
        catch (Exception &e)
        {
            delete _sockTCP;
            _sockTCP = NULL;
            _init = false;
            throw Exception(e);
        }
        _init = true;
    }
}

void	Network::handlePackets()
{
    Packet *packet;

    while ((packet = this->_factory.getPacket()))
    {
//        if (packet->getGroup() == 0 && packet->getInstruction() == 0)
//            this->getLogin(packet);
//        else if (packet->getGroup() == 0 && packet->getInstruction() == 1)
//            this->getMsgChat(packet);
//        else if (packet->getGroup() == 0 && packet->getInstruction() == 3)
//            this->getRooms(packet);
//        else if (packet->getGroup() == 0 && packet->getInstruction() == 4)
//            this->getLevels(packet);
//        else if (packet->getGroup() == 1 && packet->getInstruction() == 0)
//            return;
//        else if (packet->getGroup() == 1 && packet->getInstruction() == 1)
//            this->joinRoom(packet);
//        else if (packet->getGroup() == 1 && packet->getInstruction() == 2)
//            this->start(packet);
//        else if (packet->getGroup() == 1 && packet->getInstruction() == 3)
//            this->end(packet);
//        else if (packet->getGroup() == 1 && packet->getInstruction() == 5)
//            this->chatRoom(packet);
//        else if (packet->getGroup() == 1 && packet->getInstruction() == 6)
//            this->listLogins(packet);
//        else
//        {
            std::cout << "PACKET NON GERE" << std::endl;
            packet->show();
//        }
    }
}

void	Network::handleNetwork()
{
    if (_init)
    {
        try
        {
            handleNetworkUDP();
            handleNetworkTCP();
//            handlePackets();
        }
        catch (Exception &e)
        {
            throw Exception(e);
        }
    }
}

void	Network::pushUDP(Packet *packet)
{
    this->_sendQueueUDP.push(packet);
}

void	Network::pushTCP(Packet *packet)
{
    this->_sendQueueTCP.push(packet);
}

int     Network::getUID()
{
    return _reqUID++;
}


void	Network::handleNetworkUDP()
{
    if (_sendQueueUDP.empty() == false && _sockUDP->isWritable())
    {
        Packet	*packet = this->_sendQueueUDP.front();
        this->_sendQueueUDP.pop();
        try
        {
            _sockUDP->send(packet->serialize(), packet->size());
        }
        catch (Exception &e)
        {
            delete _sockUDP;
            _sockUDP = NULL;
            _init = false;
            throw Exception(e);
        }
        delete packet;
    }
    if (_sockUDP->isReadable())
    {
        char buffer[4098];
        int rdSize;

        try
        {
            _sockUDP->recv(buffer, 4096, &rdSize);
        }
        catch (Exception &e)
        {
            delete _sockUDP;
            _sockUDP = NULL;
            _init = false;
            throw Exception(e);
        }
        _factory.feed(buffer, rdSize);
    }
}

void	Network::handleNetworkTCP()
{
    if (_sendQueueTCP.empty() == false && _sockTCP->isWritable())
    {
        Packet	*packet = this->_sendQueueTCP.front();
        this->_sendQueueTCP.pop();
        try
        {
            _sockTCP->send(packet->serialize(), packet->size());
        }
        catch (Exception &e)
        {
            delete _sockTCP;
            _sockTCP = NULL;
            _init = false;
            throw Exception(e);
        }
        delete packet;
    }
    if (_sockTCP->isReadable())
    {
        char buffer[4096];
        int rdSize;

        try
        {
            _sockTCP->recv(buffer, 4096, &rdSize);
        }
        catch (Exception &e)
        {
            delete _sockTCP;
            _sockTCP = NULL;
            _init = false;
            throw Exception(e);
        }
        _factory.feed(buffer, rdSize);
    }
}

//void	Network::getLogin(Packet *packet)
//{
//    this->_controller->model.lobby.setLogin(packet->getStringInDataCli(1));
//    if (this->_controller->display.getVisibleDisplay() == RType::Controller::Display::LOGIN)
//    {
//        this->_controller->display.setDisplay(RType::Controller::Display::LOGIN, false);
//        this->_controller->display.setDisplay(RType::Controller::Display::LOBBY, true);
//        this->_controller->display.getDisplay(this->_controller->display.getVisibleDisplay())->updateInterface(*this->_controller->display.getWindow());
//    }
//    else
//        this->_controller->display.getDisplay(this->_controller->display.getVisibleDisplay())->updateInterface(*this->_controller->display.getWindow());
//}

//void	Network::getRooms(Packet *packet)
//{
//	int		id(0);
//	bool	spect;
//	char	maxPlayer;
//	short	idRoom;
//	std::string login;
//	std::string roomName;
//	std::string level;
//	RType::Model::Room	*room;
//	std::vector<RType::Model::Room *>	list;

//	for (unsigned int i = 0; i < packet->getDataSize();)
//	{
//		try
//		{
//			spect = packet->getIntTypeInDataCli<char>(id);
//			maxPlayer = packet->getIntTypeInDataCli<char>(id + 1);
//			idRoom = packet->getIntTypeInDataCli<short>(id + 2);
//			i = i + 10;
//			login = packet->getStringInDataCli(id + 3);
//			i += login.size() + 4;
//			roomName = packet->getStringInDataCli(id + 4);
//			i += roomName.size() + 4;
//			level = packet->getStringInDataCli(id + 5);
//			i += level.size() + 4;
//			id += 6;
//		}
//		catch (std::out_of_range &)
//		{
//			return;
//		}
//		room = new RType::Model::Room(login, roomName, level, spect, maxPlayer, idRoom, this->_controller);
//		list.push_back(room);
//	}
//	this->_controller->model.lobby.setRooms(list);
//	this->_controller->display.getDisplay(this->_controller->display.getVisibleDisplay())->updateInterface(*this->_controller->display.getWindow());
//}

//void	Network::getMsgChat(Packet *packet)
//{
//	this->_controller->model.lobby.setMsgChat(packet->getStringInDataCli(0) + " : " + packet->getStringInDataCli(1));
//	this->_controller->display.getDisplay(this->_controller->display.getVisibleDisplay())->updateInterface(*this->_controller->display.getWindow());
//}


//void	Network::getLevels(Packet *packet)
//{
//	std::vector<std::string>	list;
//	int							id = 0;

//	for (unsigned int i = 0; i < packet->getDataSize();)
//	{
//		try
//		{
//			list.push_back(packet->getStringInDataCli(id));
//			i += 4 + packet->getStringInDataCli(id).size();
//			++id;
//		}
//		catch (std::out_of_range &)
//		{
//			return;
//		}
//	}
//	this->_controller->model.lobby.setLevels(list);
//	this->_controller->display.getDisplay(this->_controller->display.getVisibleDisplay())->updateInterface(*this->_controller->display.getWindow());
//}

//void	Network::joinRoom(Packet *packet)
//{
//	std::vector<RType::Model::Room *>	list;
//	bool								found(false);

//	if (packet->getIntTypeInDataCli<char>(0))
//	{
//		list = this->_controller->model.lobby.getRooms();
//		std::cout << "Je doit trouver : " << packet->getIntTypeInDataCli<short>(1) << std::endl;
//		for (std::vector<RType::Model::Room *>::iterator it = list.begin(); it != list.end(); ++it)
//		{
//			std::cout << "Je trouve : " << (*it)->getRoomId() << std::endl;
//			if ((*it)->getRoomId() == packet->getIntTypeInDataCli<short>(1))
//			{
//				std::cout << "trouv !!" << std::endl;
//				(*it)->addPlayer(new RType::Model::Player(this->_controller->model.lobby.getLogin(), 0));
//				this->_controller->model.lobby.setActualRoom((*it));
//				found = true;
//			}
//		}
//		if (found == false)
//			return;
//		if (this->_controller->display.getVisibleDisplay() == RType::Controller::Display::LOBBY)
//		{
//			this->_controller->display.setDisplay(RType::Controller::Display::LOBBY, false);
//			this->_controller->display.setDisplay(RType::Controller::Display::ROOM, true);
//			this->_controller->display.getDisplay(this->_controller->display.getVisibleDisplay())->updateInterface(*this->_controller->display.getWindow());
//		}
//		else
//			this->_controller->display.getDisplay(this->_controller->display.getVisibleDisplay())->updateInterface(*this->_controller->display.getWindow());
//	}
//	else
//	{
//		std::cout << "Can't Join Game" << std::endl;
//	}
//}

//void	Network::start(Packet *)
//{
//	this->_controller->display.setDisplay(RType::Controller::Display::LOBBY, false);
//	this->_controller->display.setDisplay(RType::Controller::Display::GAME, true);
//	this->_controller->display.getDisplay(this->_controller->display.getVisibleDisplay())->updateInterface(*this->_controller->display.getWindow());

//}

//void	Network::end(Packet *)
//{
//  std::cout << "and that too" << std::endl;
//}

//void	Network::chatRoom(Packet *packet)
//{
//  this->_controller->model.lobby.getActualRoom()->setMsgChat(packet->getStringInDataCli(0) + " : " + packet->getStringInDataCli(1));
//  this->_controller->display.getDisplay(this->_controller->display.getVisibleDisplay())->updateInterface(*this->_controller->display.getWindow());
//}

//void	Network::listLogins(Packet *packet)
//{
//  int		id(0);
//  std::string login;
//  std::vector<RType::Model::Player *>	list;

//  for (unsigned int i = 0; i < packet->getDataSize();)
//    {
//      try
//	{
//	  i += 3;
//	  login = packet->getStringInDataCli(id + 1);
//	  i += 4 + login.size();
//	  id += 2;
//	}
//      catch (std::out_of_range &)
//	{
//	  return;
//	}
//      list.push_back(new RType::Model::Player(login, id));
//    }
//  if (!list.empty())
//    this->_controller->model.lobby.getActualRoom()->setPlayers(list);
//  this->_controller->display.getDisplay(this->_controller->display.getVisibleDisplay())->updateInterface(*this->_controller->display.getWindow());
//}

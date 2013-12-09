#include "Model/Lobby.hh"
#include "Controller/Controller.hpp"
#include "Packet.h"

RType::Model::Lobby::Lobby(Controller::Controller *controller)
	: _controller(controller), _actualRoom(NULL)
{
}

RType::Model::Lobby::Lobby(const RType::Model::Lobby &)
{
}

RType::Model::Lobby::~Lobby()
{
}

RType::Model::Lobby	&RType::Model::Lobby::operator =(const RType::Model::Lobby &other)
{
  if (this != &other)
    {
		_actualRoom = other._actualRoom;
    }
  return (*this);
}

bool									RType::Model::Lobby::addRoom(Room *room)
{
  for (std::vector<Room *>::iterator i = _rooms.begin(); i != _rooms.end();)
    {

      if ((*i)->getName() == room->getName())
	return false;
    }
  this->_rooms.push_back(room);
  return true;
}

bool									RType::Model::Lobby::rmRoom(const std::string &name)
{
  for (std::vector<Room *>::iterator i = _rooms.begin(); i != _rooms.end();)
    {
      if ((*i)->getName() == name)
	{
	  this->_rooms.erase(i);
	  return true;
	}
      else
	++i;
    }
  return false;
}

bool									RType::Model::Lobby::addPlayer(Player *player)
{
  for (std::vector<Player *>::iterator i = _players.begin(); i != _players.end();)
    {
      if ((*i)->getName() == player->getName())
	return false;
    }

  this->_players.push_back(player);
  return true;
}

bool									RType::Model::Lobby::rmPlayer(const std::string &name)
{
  for (std::vector<Player *>::iterator i = _players.begin(); i != _players.end();)
    {
      if ((*i)->getName() == name)
	{
	  this->_players.erase(i);
	  return true;
	}
      else
	++i;
    }
  return false;
}

void					RType::Model::Lobby::create(bool spectate, int maxPlayer, std::string playerName, std::string name, std::string level)
{
	Packet *tmp = new Packet();
	char	tmpMaxPlayer = maxPlayer;

	tmp->setGroup(1);
	tmp->setInstruction(0);
	tmp->updateData(6);
	tmp->appendToData<char>(0, spectate ? 1 : 0);
	tmp->appendToData<char>(1, tmpMaxPlayer);
	tmp->updateData(tmp->getDataSize() + 4 + playerName.size());
	tmp->appendToData(2, playerName.c_str());
	tmp->updateData(tmp->getDataSize() + 4 + name.size());
	tmp->appendToData(3, name.c_str());
	tmp->updateData(tmp->getDataSize() + 4 + level.size());
	tmp->appendToData(4, level.c_str());
	this->_controller->network.pushTCP(tmp);
}

void					RType::Model::Lobby::login(const std::string &name)
{
	Packet *tmp = new Packet();

	tmp->setGroup(0);
	tmp->setInstruction(0);
	tmp->updateData(name.size() + 4);
	tmp->appendToData(0, name.c_str());
	this->_controller->network.pushTCP(tmp);
}

void					RType::Model::Lobby::chat(const std::string & msg)
{
	Packet *tmp = new Packet();
	
	tmp->setGroup(0);
	tmp->setInstruction(1);
	tmp->updateData(msg.size() + 4);
	tmp->appendToData(0, msg.c_str());
	this->_controller->network.pushTCP(tmp);
}

void					RType::Model::Lobby::update()
{

}

void					RType::Model::Lobby::rooms()
{
	Packet *tmp = new Packet();

	tmp->setGroup(0);
	tmp->setInstruction(3);
	tmp->updateData(0);
	this->_controller->network.pushTCP(tmp);
}

void					RType::Model::Lobby::levels()
{
	Packet *tmp = new Packet();

	tmp->setGroup(0);
	tmp->setInstruction(4);
	tmp->updateData(0);
	this->_controller->network.pushTCP(tmp);
}

void					RType::Model::Lobby::setLogin(const std::string &name)
{
	_login = name;
}

std::string				RType::Model::Lobby::getLogin()
{
	return (_login);
}

void					RType::Model::Lobby::setRooms(std::vector<RType::Model::Room *> &rooms)
{
	for (std::vector<RType::Model::Room *>::iterator it = _rooms.begin(); it != _rooms.end(); ++it)
		delete (*it);
	_rooms.clear();
	_rooms = rooms;
}

std::vector<RType::Model::Room *>		&RType::Model::Lobby::getRooms()
{
	return (_rooms);
}

void					RType::Model::Lobby::setChat(std::vector<std::string> &chat)
{
	_chat.clear();
	_chat = chat;
}

void					RType::Model::Lobby::setMsgChat(std::string msg)
{
	_chat.push_back(msg);
}

std::vector<std::string>		&RType::Model::Lobby::getChat()
{
	return (_chat);
}

void					RType::Model::Lobby::setLevels(std::vector<std::string> &levels)
{
	_level.clear();
	_level = levels;
}

std::vector<std::string>		&RType::Model::Lobby::getLevels()
{
	return (_level);
}

void					RType::Model::Lobby::setActualRoom(RType::Model::Room *room)
{
	_actualRoom = room;
}

RType::Model::Room		*RType::Model::Lobby::getActualRoom()
{
	return _actualRoom;
}
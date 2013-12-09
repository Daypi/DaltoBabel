#include "Model/Room.hh"
#include "Controller/Controller.hpp"
#include "Packet.h"

RType::Model::Room::Room(const std::string &playerName, const std::string &name, const std::string &level, bool spectate, int maxPlayer, int roomId, Controller::Controller *controller)
	: _controller(controller), _playerName(playerName), _name(name), _level(level), _spectate(spectate), _maxPlayer(maxPlayer), _roomId(roomId)
{
}

RType::Model::Room::Room(const RType::Model::Room &other)
	: _controller(other._controller), _playerName(other._playerName), _name(other._name), _level(other._level), _spectate(other._spectate), _maxPlayer(other._maxPlayer), _roomId(other._roomId)
{
}

RType::Model::Room::~Room()
{
}

RType::Model::Room	&RType::Model::Room::operator =(const RType::Model::Room &other)
{
	if (this != &other)
	{
		_playerName = other._playerName;
		_name = other._name;
		_level = other._level;
		_spectate = other._spectate;
		_maxPlayer = other._maxPlayer;
		_roomId = other._roomId;
	}
	return (*this);
}

bool				RType::Model::Room::addPlayer(Player *player)
{
	for (unsigned int i = 0; i < this->_players.size(); ++i)
	{
		if (this->_players[i]->getName() == player->getName())
			return false;
	}

	this->_players.push_back(new Player(*player));
	return true;
}

bool				RType::Model::Room::rmPlayer(const std::string &name)
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

std::vector<RType::Model::Player *>	&RType::Model::Room::getPlayers()
{
	return (_players);
}

void				RType::Model::Room::setPlayers(std::vector<RType::Model::Player *> &players)
{
	for (std::vector<RType::Model::Player *>::iterator i = _players.begin(); i != _players.end(); ++i)
		delete ((*i));
	_players.clear();
	_players = players;
}

void				RType::Model::Room::setName(const std::string &name)
{
	this->_name = name;
}

std::string			&RType::Model::Room::getName()
{
	return (this->_name);
}

void				RType::Model::Room::join(bool spectate, short roomId, const std::string playerName)
{
	Packet *tmp = new Packet();

	tmp->setGroup(1);
	tmp->setInstruction(1);
	tmp->updateData(7);
	tmp->appendToData<char>(0, spectate ? 1 : 0);
	tmp->appendToData<short>(1, roomId);
	tmp->updateData(tmp->getDataSize() + 4 + playerName.size());
	tmp->appendToData(2, playerName.c_str());
	tmp->show();
	this->_controller->network.pushTCP(tmp);
}

void				RType::Model::Room::start()
{
	Packet *tmp = new Packet();

	tmp->setGroup(1);
	tmp->setInstruction(2);
	tmp->updateData(0);
	this->_controller->network.pushTCP(tmp);
}

void				RType::Model::Room::quit()
{
	Packet *tmp = new Packet();

	tmp->setGroup(1);
	tmp->setInstruction(4);
	tmp->updateData(0);
	this->_controller->network.pushTCP(tmp);
}

void				RType::Model::Room::chat(const std::string msg)
{
	Packet *tmp = new Packet();

	tmp->setGroup(1);
	tmp->setInstruction(5);
	tmp->updateData(msg.size() + 4);
	tmp->appendToData(0, msg.c_str());
	this->_controller->network.pushTCP(tmp);
}

void				RType::Model::Room::logins()
{
	Packet *tmp = new Packet();

	tmp->setGroup(1);
	tmp->setInstruction(6);
	tmp->updateData(0);
	this->_controller->network.pushTCP(tmp);
}

std::string			&RType::Model::Room::getLogin()
{
	return _playerName;
}

std::string			&RType::Model::Room::getLevel()
{
	return _level;
}

bool				RType::Model::Room::getSpectate() const
{
	return _spectate;
}

int					RType::Model::Room::getMaxPlayer() const
{
	return _maxPlayer;
}

int					RType::Model::Room::getRoomId() const
{
	return _roomId;
}

void					RType::Model::Room::setChat(std::vector<std::string> &chat)
{
	_chat.clear();
	_chat = chat;
}

void					RType::Model::Room::setMsgChat(std::string msg)
{
	_chat.push_back(msg);
}

std::vector<std::string>		&RType::Model::Room::getChat()
{
	return (_chat);
}
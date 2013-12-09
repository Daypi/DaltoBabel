#pragma once
#include <vector>
#include "Model/Room.hh"

namespace	RType
{
  namespace Controller
  {
    class		Controller;
  }
}

namespace RType
{
  namespace Model
  {
    class	Lobby
    {
      Controller::Controller	*_controller;
	  std::string			_login;
      std::vector<Room *>	_rooms;
	  Room					*_actualRoom;
      std::vector<Player *>	_players;
	  std::vector<std::string> _chat;
	  std::vector<std::string> _level;

    public:
      Lobby(Controller::Controller *controller);

      Lobby(const Lobby &);
      ~Lobby();

      Lobby								&operator =(const Lobby &);

      bool								addRoom(Room *room);
      bool								rmRoom(const std::string &name);
      bool								addPlayer(Player *player);
      bool								rmPlayer(const std::string &name);

      void								create(bool spectate, int maxPlayer, std::string playerName, std::string name, std::string level);
      void								login(const std::string &newName);
      void								chat(const std::string &msg);
      void								update();
      void								rooms();
      void								levels();
	  void								setLogin(const std::string &name);
	  std::string						getLogin();
	  void								setRooms(std::vector<Room *> &rooms);
	  std::vector<Room *>				&getRooms();
	  void								setChat(std::vector<std::string> &chat);
	  void								setMsgChat(std::string msg);
	  std::vector<std::string>			&getChat();
	  void								setLevels(std::vector<std::string> &levels);
	  std::vector<std::string>			&getLevels();
	  void								setActualRoom(Room *room);
	  Room								*getActualRoom();
    };
  }
}

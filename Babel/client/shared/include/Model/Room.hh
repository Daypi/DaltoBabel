#pragma once
#include <vector>
#include <list>
#include "Model/Player.hh"
#include "Model/Game.hh"

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
    class	Room
    {
      Controller::Controller		*_controller;
      std::string					_playerName;
      std::vector<Player *>				_players;
	  std::vector<std::string>	_chat;
	  std::string					_name;
      std::string					_level;
      bool						_spectate;
      int						_maxPlayer;
      int						_roomId;

    public:
      Room(const std::string &playerName, const std::string &name, const std::string &level, bool spectate, int maxPlayer, int roomId, Controller::Controller *controller);
      Room(const Room &);
      ~Room();

      Room									&operator =(const Room &);

      bool				addPlayer(Player *player);
	  bool				rmPlayer(const std::string &name);
	  std::vector<Player *>	&getPlayers();
	  void				setPlayers(std::vector<Player *> &players);


      void				setName(const std::string &name);
      std::string		&getName();
      void				join(bool spectate, short roomId, std::string playerName);
      void				start();
      void				quit();
      void				chat(std::string msg);
      void				logins();
	  std::string		&getLogin();
	  std::string		&getLevel();
	  bool				getSpectate() const;
	  int				getMaxPlayer() const;
	  int				getRoomId() const;
	  void				setChat(std::vector<std::string> &chat);
	  void				setMsgChat(std::string msg);
	  std::vector<std::string>	&getChat();
	};
  }
}

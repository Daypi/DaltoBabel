#pragma once
#include <string>

namespace RType
{
  namespace Model
  {
    class									Player
    {
      std::string					_nickname;
	  int							_id;

    public:
	  Player(const std::string &, int id);
      Player(const Player &);
      ~Player();

      Player				&operator=(const RType::Model::Player &other);
      const std::string		&getName();
      void					setName(const std::string &name);
	  int					getId();
	  void					setId(int id);
    };
  }
}

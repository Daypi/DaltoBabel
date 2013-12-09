#include "Model/Player.hh"

RType::Model::Player::Player(const std::string &name, int id)
	:_nickname(name), _id(id)
{
}

RType::Model::Player::Player(const RType::Model::Player &other)
	: _nickname(other._nickname), _id(other._id)
{
}

RType::Model::Player::~Player()
{
}

RType::Model::Player	&RType::Model::Player::operator=(const RType::Model::Player &other)
{
  if (this != &other)
    {
      this->_nickname = other._nickname;
	  this->_id = other._id;
    }
  return (*this);
}

const std::string			&RType::Model::Player::getName()
{
	return (this->_nickname);
}

void				RType::Model::Player::setName(const std::string &other)
{
	this->_nickname = other;
}

int					RType::Model::Player::getId()
{
	return _id;
}

void				RType::Model::Player::setId(int id)
{
	_id = id;
}
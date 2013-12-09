//
// Room.hh for DisplayManager in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Mon Oct 28 13:07:02 2013 martin lequeux-gruninger
// Last update Fri Nov 15 15:29:55 2013 martin lequeux-gruninger
//

#pragma	once

#include	<SFML/System.hpp>
#include	<SFML/Graphics.hpp>
#include	"Vector2.hpp"
#include	"Controller/Controller.hpp"

namespace	RType
{
  namespace	Model
  {
    class	AEntity
    {
    protected:
      Controller       	*_controller;

      My::Vector2u	_tile;
      My::Vector2f	_position;
      My::Vector2f	_direction;
      double		_speed;
      int	       	_lifeTime;
      bool		_useTilePos;
      bool		_autoUpdate;
      bool		_visible;
      bool		_boundToScreen;

      sf::Sprite		_sprite;

    public:
      AEntity(Controller *c) :
	_controller(c),
	_tile(0,0),
	_position(0,0),
	_direction(0,0),
	_speed(0),
	_lifeTime(0),
	_useTilePos(false),
	_autoUpdate(false),
	_visible(true),
	_boundToScreen(false)
      {}

      virtual		~AEntity(void) {}

    public:
      virtual void	initialize(sf::RenderWindow &w) = 0;

      virtual void	reset(sf::RenderWindow &)
      {
	_tile = sf::Vector2u(0,0);
	_position = sf::Vector2f(0,0);
	_direction = sf::Vector2f(0,0);
	_speed = 0;
	_lifeTime = 0;
	_useTilePos = false;
	_autoUpdate = false;
	_visible = true;
      }

      void		setTile(int x, int y)
      {
	this->_tile.x = x;
	this->_tile.y = y;
      }
      sf::Vector2u	getTile(void) const
      {
	return (this->_tile);
      }

      void		setPosition(float x, float y)
      {
	this->_position.x = x;
	this->_position.y = y;
      }
      sf::Vector2f	getPosition(void) const
      {
	return (this->_position);
      }

      void		setDirection(float x, float y)
      {
	this->_direction.x = x;
	this->_direction.y = y;
      }
      sf::Vector2f	getDirection(void) const
      {
	return (this->_direction);
      }

      void		setSpeed(double speed)
      {
	this->_speed = speed;
      }
      bool		getSpeed(void) const
      {
	return (this->_speed);
      }

      void		useTilePos(bool value)
      {
	this->_useTilePos = value;
      }
      bool		useTilePos(void) const
      {
	return (this->_useTilePos);
      }

      void		autoUpdate(bool value)
      {
	this->_autoUpdate = value;
      }
      bool		useAutoUpdate(void) const
      {
	return (this->_autoUpdate);
      }

      void		visible(bool visible)
      {
	this->_visible = visible;
      }

      bool		visible() const
      {
	return (this->_visible);
      }

      void		boundToScreen(bool value)
      {
	this->_boundToScreen = value;
      }

      bool		boundToScreen() const
      {
	return (this->_boundToScreen);
      }

      void		update(My::Clock &, My::Event &, My::RenderWindow &)
      {
      }

      void		tick(My::Clock &c, My::RenderWindow &w)
      {
	this->_lifeTime += c.getElapsedTime().asMilliseconds();
	if (this->_autoUpdate == true)
	  {
	    if (this->_boundToScreen == false ||
		(this->_boundToScreen &&
		 willBeFullyInScreen(this->_sprite,
				     sf::Vector2f(this->_direction.x * this->_speed * c.getElapsedTime().asMilliseconds(),
						  this->_direction.y * this->_speed * c.getElapsedTime().asMilliseconds()), w)))
	      {
		this->_position.x += this->_direction.x * this->_speed * c.getElapsedTime().asMilliseconds();
		this->_position.y += this->_direction.y * this->_speed * c.getElapsedTime().asMilliseconds();
	      }
	  }
      }

      void		unload(void)
      {
      }
  }
}

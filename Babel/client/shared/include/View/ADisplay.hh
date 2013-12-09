//
// IDisplay.hpp for rtype in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Mon Oct 28 15:20:36 2013 martin lequeux-gruninger
// Last update Sat Nov 16 14:03:45 2013 martin lequeux-gruninger
//

#pragma	once

#include	"View/IDisplay.hh"
#include	"Controller/Controller.hpp"

namespace	RType
{
  namespace	View
  {
    class	ADisplay : public IDisplay
    {
    protected:
      bool			_visible;
      Controller::Controller	*_controller;

    public:
      ADisplay(Controller::Controller *controller)
      {
	this->_visible = false;
	this->_controller = controller;
      }

      virtual		~ADisplay(void) {}

    public:
      virtual void	initialize(My::RenderWindow &w) = 0;
      virtual void	reset(My::RenderWindow &w) = 0;
      virtual void	update(My::Clock &c, My::Event &e, My::RenderWindow &w) = 0;
      virtual void	guiEvent(My::Clock &c, My::Callback &e, My::RenderWindow &w) = 0;
	  virtual void	loadInterface(My::RenderWindow &w) = 0;
	  virtual void	updateInterface(My::RenderWindow &w) = 0;
      virtual void	unloadInterface(My::RenderWindow &w) = 0;
      virtual void	tick(My::Clock &c, My::RenderWindow &w) = 0;
      virtual void	draw(My::RenderWindow &w) = 0;
      virtual void	unload(void) = 0;
      virtual void	visible(bool visible, My::RenderWindow &w)
      {
	if (this->_visible == false && visible == true)
	  {
	    this->reset(w);
	    this->unloadInterface(w);
	  }
	if (this->_visible == true && visible == false)
	{
		this->unloadInterface(w);
		this->_visible = visible;
		return;
	}
	this->loadInterface(w);
	//this->updateInterface(w);
	this->_visible = visible;
      }

      virtual bool	visible() const
      {
	return (this->_visible);
      }

      static void		normalize(sf::Vector2f &vec)
      {
	vec /= (float)sqrt((vec.x * vec.x) +
			   (vec.y * vec.y));
      }

      static float	dot(const sf::Vector2f &vec1, const sf::Vector2f &vec2)
      {
	return (vec1.x * vec2.x + vec1.y * vec2.y);
      }

      static sf::Vector2f	mult(double value, sf::Vector2f &vec)
      {
	vec.x *= value;
	vec.y *= value;
	return (vec);
      }

      static bool		isInRectangle(const sf::Vector2f &point, const sf::FloatRect &rect)
      {
	sf::Vector2f p1(rect.left, rect.top);
	sf::Vector2f p2(rect.left + rect.width, rect.top);
	sf::Vector2f p3(rect.left + rect.width, rect.top + rect.height);
	sf::Vector2f p4(rect.left, rect.top + rect.height);
	sf::Vector2f p(point);

	sf::Vector2f p1p4 = p1 - p4;
	sf::Vector2f p3p4 = p3 - p4;
	sf::Vector2f twoPC = (mult(2.0, p) - p1 - p3);

	return ((dot(p3p4, twoPC - p3p4) <= 0 &&
		 dot(p3p4, twoPC + p3p4) >= 0) &&
		(dot(p1p4, twoPC - p1p4) <= 0 &&
		 dot(p1p4, twoPC + p1p4) >= 0));
      }

      static bool		isInScreen(const sf::Vector2f &point,
					   sf::RenderWindow &w)
      {
	return (isInRectangle(point, sf::FloatRect(0, 0, w.getSize().x, w.getSize().y)));
      }

      static bool		isInScreen(const sf::Sprite &sprite,
					   My::RenderWindow &w)
      {
	return (sprite.getGlobalBounds().intersects(sf::FloatRect(0, 0, w.getSize().x, w.getSize().y)));
      }

      static bool		isFullyInScreen(const sf::Sprite &sprite,
						My::RenderWindow &w)
      {
	return (isInRectangle(sf::Vector2f(sprite.getGlobalBounds().left,
					   sprite.getGlobalBounds().top),
			      sf::FloatRect(0, 0, w.getSize().x, w.getSize().y)) &&
		isInRectangle(sf::Vector2f(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width,
					   sprite.getGlobalBounds().top),
			      sf::FloatRect(0, 0, w.getSize().x, w.getSize().y)) &&
		isInRectangle(sf::Vector2f(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width,
					   sprite.getGlobalBounds().top + sprite.getGlobalBounds().height),
			      sf::FloatRect(0, 0, w.getSize().x, w.getSize().y)) &&
		isInRectangle(sf::Vector2f(sprite.getGlobalBounds().left,
					   sprite.getGlobalBounds().top + sprite.getGlobalBounds().height),
			      sf::FloatRect(0, 0, w.getSize().x, w.getSize().y)));
      }

      static bool		willBeFullyInScreen(const sf::Sprite &sprite,
						    const sf::Vector2f &move,
						    My::RenderWindow &w)
      {
	return (isInRectangle(sf::Vector2f(sprite.getGlobalBounds().left + move.x,
					   sprite.getGlobalBounds().top + move.y),
			      sf::FloatRect(0, 0, w.getSize().x, w.getSize().y)) &&
		isInRectangle(sf::Vector2f(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width + move.x,
					   sprite.getGlobalBounds().top + move.y),
			      sf::FloatRect(0, 0, w.getSize().x, w.getSize().y)) &&
		isInRectangle(sf::Vector2f(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width + move.x,
					   sprite.getGlobalBounds().top + sprite.getGlobalBounds().height + move.y),
			      sf::FloatRect(0, 0, w.getSize().x, w.getSize().y)) &&
		isInRectangle(sf::Vector2f(sprite.getGlobalBounds().left + move.x,
					   sprite.getGlobalBounds().top + sprite.getGlobalBounds().height + move.y),
			      sf::FloatRect(0, 0, w.getSize().x, w.getSize().y)));
      }

      virtual int		zIndex(void) = 0;
    };
  }
}

//
// DisplayController.hh for DisplayController in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Mon Oct 28 13:07:02 2013 martin lequeux-gruninger
// Last update Sat Nov 16 23:51:35 2013 martin lequeux-gruninger
//

#pragma	once

#include	<vector>

namespace	RType
{
  namespace Controller
  {
    class		Controller;
  }
  namespace View
  {
    class		StarField;
  }
}

#include	"Controller/Core.hpp"
#include	"View/IDisplay.hh"

namespace	RType
{
  namespace Controller
  {
    class	Display : public Core
    {
    private:
      std::vector<View::IDisplay *>		_displays;
      Controller				*_controller;
      View::StarField				*_starField;

    public:
      enum	Displays
	{
	  GAME = 0,
	  INTRO = 1,
	  MENU = 2,
	  LOBBY = 3,
	  ROOM = 4,
	  LOGIN = 5,
		
	  COUNT
	};

    private:
      Display		&operator=(const Display &);
      Display(const Display &);

    public:
      Display(Controller *controller);
      virtual		~Display(void) {}

    public:
      int			getScreenWidth() const
      {
	return (this->screenWidth);
      }

      int			getScreenHeight() const
      {
	return (this->screenHeight);
      }

      View::IDisplay *		getDisplay(enum Displays d)
      {
		if (d == COUNT)
			return (_displays[0]);
		return (_displays[d]);

      }

	  void					setDisplay(enum Displays d, bool b)
	  {
		  for (int i = 0; i < Displays::COUNT; ++i)
			  this->_displays[d]->visible(false, *this->_window);
		  this->_displays[d]->visible(b, *this->_window);
	  }

	  enum Displays 	getVisibleDisplay()
	  {
		  for (int i = 0; i < Displays::COUNT; ++i)
		  if (this->_displays[i]->visible())
			  return ((enum Displays)i);
		  return Displays::COUNT;
	  }

    public:
      static sf::Vector2f	getScale(const My::RenderWindow &w)
      {
	//ALL TEXTURES SHOULD BE MADE TO FIT A 1080p SCREEN
	return (sf::Vector2f((float)w.getSize().x  / 1920,
			     (float)w.getSize().y / 1080));
      }

    protected:
      virtual void	initialize(My::RenderWindow &w);
      virtual void	update(My::Clock &c, My::Event &e, My::RenderWindow &w);
      virtual void	guiEvent(My::Clock &c, My::Callback &e, My::RenderWindow &w);
      virtual void	tick(My::Clock &c, My::RenderWindow &w);
      virtual void	draw(My::RenderWindow &w);
      virtual void	unload(void);
    };
  }
}

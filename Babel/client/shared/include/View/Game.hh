//
// Menu.hh for DisplayManager in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Mon Oct 28 13:07:02 2013 martin lequeux-gruninger
// Last update Sat Nov 16 14:02:18 2013 martin lequeux-gruninger
//

#pragma	once

#include	"View/ADisplay.hh"
#include	"Controller/Controller.hpp"

namespace	RType
{
  namespace	View
  {
    class	Game : public ADisplay
    {
      bool		_visible;

    public:
      Game(Controller::Controller *c) :
	ADisplay(c) {}
      virtual		~Game(void) {}

    public:
      virtual void	initialize(My::RenderWindow &w);
      virtual void	reset(My::RenderWindow &w);
      virtual void	update(My::Clock &c, My::Event &e, My::RenderWindow &w);
      virtual void	guiEvent(My::Clock &c, My::Callback &e, My::RenderWindow &w);
	  virtual void	loadInterface(My::RenderWindow &w);
	  virtual void	updateInterface(My::RenderWindow &w);
	  virtual void	unloadInterface(My::RenderWindow &w);
      virtual void	tick(My::Clock &c, My::RenderWindow &w);
      virtual void	draw(My::RenderWindow &w);
      virtual void	unload(void);
      virtual int		zIndex(void);
    };
  }
}

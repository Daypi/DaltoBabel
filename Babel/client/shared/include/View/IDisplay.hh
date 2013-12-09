//
// IDisplay.hpp for rtype in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Mon Oct 28 15:20:36 2013 martin lequeux-gruninger
// Last update Sat Nov 16 14:04:16 2013 martin lequeux-gruninger
//

#pragma	once

#include	"View/MySFML.hpp"

namespace	RType
{
  namespace	View
  {
    class	IDisplay
    {
    public:
      virtual void	initialize(My::RenderWindow &w) = 0;
      virtual void	update(My::Clock &c, My::Event &e, My::RenderWindow &w) = 0;
      virtual void	guiEvent(My::Clock &c, My::Callback &e, My::RenderWindow &w) = 0;
      virtual void	loadInterface(My::RenderWindow &w) = 0;
	  virtual void	updateInterface(My::RenderWindow &w) = 0;
      virtual void	unloadInterface(My::RenderWindow &w) = 0;
      virtual void	tick(My::Clock &c, My::RenderWindow &w) = 0;
      virtual void	draw(My::RenderWindow &w) = 0;
      virtual void	unload(void) = 0;
      virtual void	visible(bool, My::RenderWindow &w) = 0;
      virtual bool	visible() const = 0;
      virtual int		zIndex(void) = 0;
    };
  }
}

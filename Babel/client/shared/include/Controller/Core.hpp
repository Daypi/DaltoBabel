//
// Display.hpp for rtype in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Mon Oct 28 10:35:53 2013 martin lequeux-gruninger
// Last update Sat Nov 16 23:54:14 2013 martin lequeux-gruninger
//

#pragma	once

#include	<cstdint>
#include	<sstream>
#include	"View/MySFML.hpp"

namespace	RType
{
  namespace Controller
  {
    class		Controller;
  }
}

namespace	RType
{
  namespace	Controller
  {
    class	Core
    {
	protected:
      Controller				*_controller;
	  My::RenderWindow			*_window;
	  bool						_askClose;

    public:
      Core(Controller *controller)
	: _controller(controller) {}
      virtual		~Core() {}
      void		run(int x = 800,
			    int y = 600,
			    const std::string &title = "Main Window",
			    uint32_t style = My::Style::Close);
	  My::RenderWindow	*getWindow() const;
	  void			askClose();

    protected:
      virtual void	initialize(My::RenderWindow &w) = 0;
      virtual void	update(My::Clock &c, My::Event &e, My::RenderWindow &w) = 0;
      virtual void	guiEvent(My::Clock &c, My::Callback &e, My::RenderWindow &w) = 0;
      virtual void	tick(My::Clock &c, My::RenderWindow &w) = 0;
      virtual void	draw(My::RenderWindow &w) = 0;
      virtual void	unload(void) = 0;

      int			screenWidth;
      int			screenHeight;
    };
  }
}

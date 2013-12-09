//
// Room.hh for DisplayManager in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Mon Oct 28 13:07:02 2013 martin lequeux-gruninger
// Last update Sat Nov 16 14:02:42 2013 martin lequeux-gruninger
//

#pragma	once

#include	"View/ADisplay.hh"

namespace	RType
{
  namespace	View
  {
    class	Room : public ADisplay
    {
		tgui::Button*	back;
		tgui::Label*	players;
		tgui::ListBox*	playerList;
		tgui::Panel*	rightSideUp;
		tgui::Panel*	rightSide;
		tgui::Panel*	rightSideDown;
		tgui::ListBox*	chatList;
		tgui::Panel*	leftSide;
		tgui::Button*	exit;
		tgui::Label*	room;
		tgui::Label*	roomName;
		tgui::Label*	maxPlayer;
		tgui::Label*	level;
		tgui::Label*	spectate;
		tgui::Button*	start;
		tgui::Button*	ready;
		tgui::EditBox*	msgChat;
		tgui::Button*	send;

    public:
      Room(Controller::Controller *c) :
	ADisplay(c) {}
      virtual		~Room(void) {}

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
      virtual int	zIndex(void);
    };
  }
}

//
// Lobby.hh for DisplayManager in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Mon Oct 28 13:07:02 2013 martin lequeux-gruninger
// Last update Sat Nov 16 15:28:32 2013 martin lequeux-gruninger
//

#pragma	once

#include	"View/ADisplay.hh"
#include	"Controller/Controller.hpp"

namespace	RType
{
  namespace	View
  {
    class	Lobby : public ADisplay
    {
      tgui::Label*	rooms;
      tgui::ListBox*	roomList;
      tgui::Panel*	rightSideUp;
      tgui::Panel*	rightSide;
      tgui::Panel*	rightSideDown;
      tgui::ListBox*	chatList;
      tgui::Panel*	leftSide;
      tgui::EditBox*	name;
      tgui::Button*	ok;
      tgui::Label*	room;
      tgui::EditBox*	roomName;
      tgui::Checkbox*	spectate;
      tgui::Label*	maxPlayer;
      tgui::ComboBox*	listPLayers;
      tgui::Label*	level;
      tgui::ComboBox*	listLevel;
	  tgui::Button*	back;
	  tgui::Button*	create;
	  tgui::Button*	join;
      tgui::EditBox*	msgChat;
      tgui::Button*	send;

    public:
      Lobby(Controller::Controller *c) :
	ADisplay(c) {}
      virtual		~Lobby(void) {}

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

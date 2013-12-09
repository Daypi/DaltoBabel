//
// DisplayController.cpp for rtype in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Mon Oct 28 13:12:07 2013 martin lequeux-gruninger
// Last update Sat Nov 16 23:51:03 2013 martin lequeux-gruninger
//

#include	<iostream>
#include	"Controller/Display.hh"
#include	"View/Intro.hh"
#include	"View/StarField.hh"
#include	"View/Menu.hh"
#include	"View/Lobby.hh"
#include	"View/Game.hh"
#include	"View/Room.hh"
#include	"View/Login.hh"


RType::Controller::Display::Display(Controller *controller)
  : Core(controller)
{
  this->_controller = controller;
  this->_starField = new View::StarField(this->_controller);
}

void	RType::Controller::Display::initialize(My::RenderWindow &w)
{
  this->_displays.push_back(new View::Game(_controller));
  this->_displays.push_back(new View::Intro(_controller));
  this->_displays.push_back(new View::Menu(_controller));
  this->_displays.push_back(new View::Lobby(_controller));
  this->_displays.push_back(new View::Room(_controller));
  this->_displays.push_back(new View::Login(_controller));

  std::vector<View::IDisplay *>::iterator end = this->_displays.end();
  for (std::vector<View::IDisplay *>::iterator it = this->_displays.begin(); it != end; ++it)
    if ((*it))
      (*it)->initialize(w);

  this->_starField->visible(true, w);
  this->_starField->initialize(w);
  this->_starField->reset(w);

  this->_displays[INTRO]->visible(true, w);
}

void	RType::Controller::Display::update(My::Clock &c, My::Event &e, My::RenderWindow &w)
{
  if (this->_starField->visible())
    this->_starField->update(c, e, w);
  std::vector<View::IDisplay *>::iterator end = this->_displays.end();
  for (std::vector<View::IDisplay *>::iterator it = this->_displays.begin(); it != end; ++it)
    if ((*it) && (*it)->visible())
      (*it)->update(c, e, w);
}

void	RType::Controller::Display::guiEvent(My::Clock &c, My::Callback &e, My::RenderWindow &w)
{
  if (this->_starField->visible())
    this->_starField->guiEvent(c, e, w);
  std::vector<View::IDisplay *>::iterator end = this->_displays.end();
  for (std::vector<View::IDisplay *>::iterator it = this->_displays.begin(); it != end; ++it)
    if ((*it) && (*it)->visible())
      (*it)->guiEvent(c, e, w);
}

void	RType::Controller::Display::tick(My::Clock &c, My::RenderWindow &w)
{
  if (this->_starField->visible())
    this->_starField->tick(c, w);
  std::vector<View::IDisplay *>::iterator end = this->_displays.end();
  for (std::vector<View::IDisplay *>::iterator it = this->_displays.begin(); it != end; ++it)
    if ((*it) && (*it)->visible())
      (*it)->tick(c, w);
}

void	RType::Controller::Display::draw(My::RenderWindow &w)
{
  if (this->_starField->visible())
    this->_starField->draw(w);
  std::vector<View::IDisplay *>::iterator end = this->_displays.end();
  for (std::vector<View::IDisplay *>::iterator it = this->_displays.begin(); it != end; ++it)
    if ((*it) && (*it)->visible())
      (*it)->draw(w);
}

void	RType::Controller::Display::unload(void)
{
  this->_starField->unload();
  std::vector<View::IDisplay *>::iterator end = this->_displays.end();
  for (std::vector<View::IDisplay *>::iterator it = this->_displays.begin(); it != end; ++it)
    if ((*it))
      (*it)->unload();
}


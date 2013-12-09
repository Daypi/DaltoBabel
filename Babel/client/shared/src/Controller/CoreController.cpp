//
// DisplayController.cpp for rtype in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Mon Oct 28 13:12:07 2013 martin lequeux-gruninger
// Last update Sun Nov 24 21:41:51 2013 martin lequeux-gruninger
//

#include	<iostream>
#include	"Controller/Core.hpp"
#include	"Controller/Controller.hpp"
#include	"Controller/Network.hpp"

void	RType::Controller::Core::run(int x, int y, const std::string &title, uint32_t style)
{
  this->_window = new My::RenderWindow(x, y, title, style);
  My::Clock		fpsClock;
  My::Clock		clock;
  bool			showFps = false; //SET TO TRUE FOR DEBUG PURPOSES

  this->screenWidth = x;
  this->screenHeight = y;

  this->_window->globalFont.loadFromFile("./../shared/ressources/TGUI/Fonts/DejaVuSans.ttf");

  //INITAILIZE
  this->initialize(*_window);

  this->_window->setFramerateLimit(60);
  this->_window->setVerticalSyncEnabled(true);
  this->_askClose = false;
  while (this->_window->isOpen() && !this->_askClose)
    {
		//NETWORK
		this->_controller->network.handleNetwork();

      //UPDATE
      My::Event event;
      while (this->_window->pollEvent(event))
	{
		if (event.type == My::Event::Closed ||
			((event.type == My::Event::KeyPressed) && (event.key.code == My::Keyboard::Escape)))
		{
			this->_window->removeAllObjects();
			this->_window->close();
			return;
		}
	  this->_window->handleEvent(event);
	  this->update(clock, event, *_window);
	}

      // //GUI CALLBACKS
      My::Callback callback;
      while (this->_window->getCallback(callback))
	this->guiEvent(clock, callback, *_window);
	  if (this->_askClose)
		  break;
      //TICK
      if (clock.getElapsedTime() > 0.015)
	{
	  this->tick(clock, *_window);
	  clock.restart();
	}

      this->_window->clear();

      //DRAW
      this->draw(*_window);

      if (showFps == true)
	std::cout <<  (1.0 / (fpsClock.restart())) << std::endl;
      else
	fpsClock.restart();
      this->_window->drawGUI();
      this->_window->display();

    }
  //UNLOAD
  this->unload();
}

My::RenderWindow	*RType::Controller::Core::getWindow() const
{
	return this->_window;
}

void				RType::Controller::Core::askClose()
{
	this->_askClose = true;
}

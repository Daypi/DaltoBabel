//
// TexturesController.hpp for rtype in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Tue Oct 29 09:27:15 2013 martin lequeux-gruninger
// Last update Wed Nov 20 16:15:06 2013 martin lequeux-gruninger
//

#pragma		once

#include	<iostream>
#include	<SFML/System.hpp>
#include	<SFML/Graphics.hpp>
#include	"Model/Lobby.hh"

namespace	RType
{
  namespace Controller
  {
    class		Controller;
  }
}

namespace	RType
{
  namespace Controller
  {
    class		Model
    {
    Controller		*_controller;

    private:
      Model		&operator=(const Model &);
      Model(const Model &);

    public:
      Model(Controller *controller)
	: lobby(controller)
      {
	_controller = controller;
      }

      ~Model() {}

      RType::Model::Lobby		lobby;
    };
  }
}

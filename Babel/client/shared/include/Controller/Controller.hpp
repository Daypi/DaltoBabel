//
// TexturesController.hpp for rtype in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Tue Oct 29 09:27:15 2013 martin lequeux-gruninger
// Last update Wed Nov 20 16:07:30 2013 martin lequeux-gruninger
//

#pragma		once

#include	<iostream>
#include	<SFML/System.hpp>
#include	<SFML/Graphics.hpp>
#include	<random>

#include	"Resources.hpp"
#include	"Network.hpp"
#include	"Model.hpp"
#include	"Display.hh"

namespace	RType
{
  namespace Controller
  {
    class		Controller
    {
      std::mt19937	_generator;

    private:
      Controller		&operator=(const Controller &);
      Controller(const Controller &);

    public:
		Controller() :
			network(this), model(this), resources(), display(this)
      {
	_generator.seed(42);
      }
      ~Controller() {}

    public:
      int		randomBetween(int start, int end)
      {
	std::uniform_int_distribution<int> dist_n(start, end);
	return (dist_n(_generator));
      }

    public:
      Network			network;
      Model				model;
	  Resources			resources;
	  Display			display;
    };
  }
}

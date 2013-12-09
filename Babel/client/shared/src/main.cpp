//
// main.cpp for rtype in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Mon Oct 28 09:35:10 2013 martin lequeux-gruninger
// Last update Sat Nov 16 21:23:56 2013 martin lequeux-gruninger
//

#include	<iostream>
#include	"Controller/Controller.hpp"

bool			envIsValid(char **env)
{
  int			cpt = -1;

  while ((env) && (env[++cpt]))
    if ((std::string(env[cpt]) == "DISPLAY=:0.0") ||
	(std::string(env[cpt]) == "DISPLAY=:0"))
      return (true);
  return (false);
}

int main(int, char **, char **env)
{
  RType::Controller::Controller	rtype;

#ifndef _WIN32
  if (envIsValid(env) == false)
    {
      std::cerr << "Error: Invalid environment." << std::endl;
      return (EXIT_FAILURE);
    }
#endif	//_WIN32

  //rtype.display.run(1920, 1080, "RTYPE RULEZ", My::Style::Fullscreen);
  rtype.display.run(1280, 720, "RTYPE RULEZ");
  return (EXIT_SUCCESS);
}

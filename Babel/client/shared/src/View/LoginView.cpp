//
// Menu.cpp for rtype in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Mon Oct 28 13:12:07 2013 martin lequeux-gruninger
// Last update Sun Nov 24 21:31:07 2013 martin lequeux-gruninger
//

#include	"View/Login.hh"
#include	"Util.hpp"

void	RType::View::Login::initialize(My::RenderWindow &w)
{
  this->reset(w);
}

void	RType::View::Login::reset(My::RenderWindow &w)
{
  w.setMouseCursorVisible(true);
}

void	RType::View::Login::update(My::Clock &, My::Event &, My::RenderWindow &)
{
}

void	RType::View::Login::guiEvent(My::Clock &, My::Callback &c, My::RenderWindow &)
{
    if (c.callbackID == 1)
    {
        if (c.trigger == tgui::Callback::mouseClick)
	  {
	    int p;

	    std::string ip = _ipEditBox->getText();
		std::string port = _portEditBox->getText();

	    p = Util::fromString<int>(port);
	    this->_controller->network.connect(ip, p);
	  }
    }
}

void	RType::View::Login::loadInterface(My::RenderWindow &w)
{
	w.removeAllObjects();

  _ipEditBox = w.add<tgui::EditBox>("ip");
  _ipEditBox->load("./../shared/ressources/TGUI/objects/EditBox/White");
  _ipEditBox->setBorders(6, 4, 6, 4);
  _ipEditBox->setSize(w.getSize().x / 3, w.getSize().y / 20);
  _ipEditBox->setText("10.45.20.245");
  _ipEditBox->setPosition((w.getSize().x / 2 - _ipEditBox->getSize().x / 2),
			  (w.getSize().y / 2 - _ipEditBox->getSize().y / 2) - (w.getSize().y / 20) * 2);

  _portEditBox = w.add<tgui::EditBox>("port");
  _portEditBox->load("./../shared/ressources/TGUI/objects/EditBox/White");
  _portEditBox->setBorders(6, 4, 6, 4);
  _portEditBox->setSize(w.getSize().x / 3, w.getSize().y / 20);
  _portEditBox->setText("11235");
  _portEditBox->setPosition((w.getSize().x / 2 - _portEditBox->getSize().x / 2),
			    (w.getSize().y / 2 - _portEditBox->getSize().y / 2));

  _ok = w.add<tgui::Button>("ok");
  _ok->load("./../shared/ressources/TGUI/objects/Button/White");
  _ok->setText("OK");
  _ok->setSize(w.getSize().x / 3, w.getSize().y / 20);
  _ok->setPosition((w.getSize().x / 2 - _ok->getSize().x / 2),
		   (w.getSize().y / 2 - _ok->getSize().y / 2) + (w.getSize().y / 20) * 2);
  _ok->callbackID = 1;
}

void	RType::View::Login::updateInterface(My::RenderWindow &)
{
}

void	RType::View::Login::unloadInterface(My::RenderWindow &w)
{
	w.removeAllObjects();
	//w.remove(_ok);
	//w.remove(_portEditBox);
	//w.remove(_ipEditBox);
	//std::vector<tgui::OBJECT *>& toto = w.getObjects();
	//for (int i = 0; i < toto.size(); ++i)
	//	std::cout << i << " olol" << std::endl;
	//std::cout << "erase" << std::endl;
}

void	RType::View::Login::tick(My::Clock &, My::RenderWindow &)
{
}

void	RType::View::Login::draw(My::RenderWindow &w)
{
	if (this->_visible)
	{
		w.draw(*_ok, sf::RenderStates::Default);
		w.draw(*_ipEditBox, sf::RenderStates::Default);
		w.draw(*_portEditBox, sf::RenderStates::Default);
	}
}

void	RType::View::Login::unload(void)
{
}

int	RType::View::Login::zIndex(void)
{
  return (2);
}

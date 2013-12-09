//
// Menu.cpp for rtype in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Mon Oct 28 13:12:07 2013 martin lequeux-gruninger
// Last update Sat Nov 16 14:43:09 2013 martin lequeux-gruninger
//

#include	"View/Menu.hh"
#include	"View/Login.hh"
#include	"View/Lobby.hh"

void	RType::View::Menu::initialize(My::RenderWindow &w)
{
  sf::Texture *tex;

  if ((tex = this->_controller->resources.getTexture("introBG")))
    {
      this->_backgroundSprite.setTexture(*tex);
      this->_backgroundSprite.setScale(Controller::Display::getScale(w));
      this->_backgroundSprite.setPosition(0, -(float)w.getSize().y / 5);
    }

  if ((tex = this->_controller->resources.getTexture("playText")))
    {
      this->_playSprite.setTexture(*tex);
      this->_playSprite.setOrigin(this->_playSprite.getLocalBounds().width / 2,
				  this->_playSprite.getLocalBounds().height / 2);
      this->_playSprite.setScale(Controller::Display::getScale(w));
      this->_playSprite.setPosition((w.getSize().x / 4),
				    w.getSize().y - (w.getSize().y / 5));
    }

  if ((tex = this->_controller->resources.getTexture("optionsText")))
    {
      this->_optionsSprite.setTexture(*tex);
      this->_optionsSprite.setOrigin(this->_optionsSprite.getLocalBounds().width / 2,
				     this->_optionsSprite.getLocalBounds().height / 2);
      this->_optionsSprite.setScale(Controller::Display::getScale(w));
      this->_optionsSprite.setPosition(w.getSize().x - (w.getSize().x / 4),
				       w.getSize().y - (w.getSize().y / 5));
    }

  if ((tex = this->_controller->resources.getTexture("selector")))
    {
      this->_selectorSprite.setTexture(*tex);
      this->_selectorSprite.setOrigin(this->_selectorSprite.getLocalBounds().width / 2,
				      this->_selectorSprite.getLocalBounds().height / 2);
      this->_selectorSprite.setScale(Controller::Display::getScale(w));
    }
  this->_optionsSelectorPosition.push_back(sf::Vector2u(this->_playSprite.getPosition().x - this->_selectorSprite.getGlobalBounds().width * 2 - this->_playSprite.getGlobalBounds().width / 2,
							this->_playSprite.getPosition().y));
  this->_optionsSelectorPosition.push_back(sf::Vector2u(this->_optionsSprite.getPosition().x - this->_selectorSprite.getGlobalBounds().width * 2 - this->_optionsSprite.getGlobalBounds().width / 2,
							this->_optionsSprite.getPosition().y));
  this->reset(w);
}

void	RType::View::Menu::reset(My::RenderWindow &w)
{
  w.setMouseCursorVisible(false);
  this->_option = 0;
  this->_selectorSprite.setPosition(this->_optionsSelectorPosition[this->_option].x,
				    this->_optionsSelectorPosition[this->_option].y);

}

void	RType::View::Menu::update(My::Clock &, My::Event &e, My::RenderWindow &w)
{
  if (((e.type == My::Event::KeyPressed) && (e.key.code == My::Keyboard::Right)) ||
      ((e.type == My::Event::KeyPressed) && (e.key.code == My::Keyboard::Tab)))
    this->_option += 1;
  if (((e.type == My::Event::KeyPressed) && (e.key.code == My::Keyboard::Left)))
    this->_option -= 1;
  this->_option %= this->_optionsSelectorPosition.size();
  this->_selectorSprite.setPosition(this->_optionsSelectorPosition[this->_option].x,
				    this->_optionsSelectorPosition[this->_option].y);
  if ((((e.type == My::Event::KeyPressed) && (e.key.code == My::Keyboard::Space)) ||
       ((e.type == My::Event::KeyPressed) && (e.key.code == My::Keyboard::Return))) &&
      this->_option == 0)
    {
      this->_controller->display.getDisplay(Controller::Display::LOGIN)->visible(true, w);
      this->visible(false, w);
    }
  else if ((((e.type == My::Event::KeyPressed) && (e.key.code == My::Keyboard::Space)) ||
	    ((e.type == My::Event::KeyPressed) && (e.key.code == My::Keyboard::Return))) &&
	   this->_option == 1)
    {
      this->_controller->display.getDisplay(Controller::Display::LOBBY)->visible(true, w);
      this->visible(false, w);
    }
}

void	RType::View::Menu::guiEvent(My::Clock &, My::Callback &, My::RenderWindow &)
{
}

void	RType::View::Menu::loadInterface(My::RenderWindow &w)
{
	w.removeAllObjects();
}

void	RType::View::Menu::updateInterface(My::RenderWindow &)
{
}

void	RType::View::Menu::unloadInterface(My::RenderWindow &)
{
}

void	RType::View::Menu::tick(My::Clock &c, My::RenderWindow &)
{
  this->_selectorSprite.rotate(100 * c.getElapsedTime());
}

void	RType::View::Menu::draw(My::RenderWindow &w)
{
  w.draw(this->_backgroundSprite);
  w.draw(this->_playSprite);
  w.draw(this->_optionsSprite);
  w.draw(this->_selectorSprite);
}

void	RType::View::Menu::unload(void)
{
}

int	RType::View::Menu::zIndex(void)
{
  return (2);
}

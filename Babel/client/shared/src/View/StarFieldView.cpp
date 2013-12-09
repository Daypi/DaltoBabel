//
// StarField.cpp for rtype in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Mon Oct 28 13:12:07 2013 martin lequeux-gruninger
// Last update Sat Nov 16 14:00:36 2013 martin lequeux-gruninger
//

#include	"View/StarField.hh"

void	RType::View::StarField::initialize(My::RenderWindow &w)
{
  for (int i = 0; i < 10; ++i)
    {
      sf::Sprite *sprite = new sf::Sprite;
      sf::Texture *tex;
      if ((tex = this->_controller->resources.getTexture("starsTile")))
	{
	  sprite->setTexture(*tex);
	  sprite->setScale(Controller::Display::getScale(w));
	  sprite->setColor(sf::Color(255, 255, 255, 100));
	  this->_starsTilesPool.push_back(sprite);
	}
    }
  for (int i = 0; i < 10; ++i)
    {
      sf::Sprite *sprite = new sf::Sprite;
      sf::Texture *tex;
      if ((tex = this->_controller->resources.getTexture("BGStarsTile")))
	{
	  sprite->setTexture(*tex);
	  sprite->setScale(Controller::Display::getScale(w));
	  sprite->setColor(sf::Color(255, 255, 255, 100));
	  this->_BGStarsTilesPool.push_back(sprite);
	}
    }
  this->reset(w);
}

void	RType::View::StarField::reset(My::RenderWindow &)
{
}

void	RType::View::StarField::update(My::Clock &, My::Event &, My::RenderWindow &)
{
}

void	RType::View::StarField::guiEvent(My::Clock &, My::Callback &, My::RenderWindow &)
{
}

void	RType::View::StarField::loadInterface(My::RenderWindow &)
{
}

void	RType::View::StarField::updateInterface(My::RenderWindow &)
{
}

void	RType::View::StarField::unloadInterface(My::RenderWindow &)
{
}

void	RType::View::StarField::addTile(My::RenderWindow &w)
{
  //STARS
  if (this->_starsTilesPool.empty())
    {
      for (int i = 0; i < 2; ++i)
	{
	  sf::Sprite *sprite = new sf::Sprite;
	  sf::Texture *tex;
	  if ((tex = this->_controller->resources.getTexture("starsTile")))
	    {
	      sprite->setTexture(*tex);
	      sprite->setScale(Controller::Display::getScale(w));
	      sprite->setColor(sf::Color(255, 255, 255, 100));
	      this->_starsTilesPool.push_back(sprite);
	    }
	}
    }
  if (this->_starsTilesPool.empty() == false)
    {
      sf::Sprite *tile = this->_starsTilesPool.back();
      this->_starsTilesPool.pop_back();
      tile->setOrigin(tile->getLocalBounds().width / 2, tile->getLocalBounds().height / 2);
      tile->setPosition(w.getSize().x + tile->getGlobalBounds().width / 2, w.getSize().y / 2);
      tile->setRotation(0);
      //SPRITE RANDOMISATION
      //FLIPX
      if (this->_controller->randomBetween(0, 1) == 0)
	{
	  tile->setTextureRect(sf::Rect<int>(tile->getTexture()->getSize().x, 0,
					     -(int)tile->getTexture()->getSize().x, tile->getTexture()->getSize().y));
	}
      //FLIPY
      if (this->_controller->randomBetween(0, 1) == 0)
	{
	  tile->setTextureRect(sf::Rect<int>(0, tile->getTexture()->getSize().y,
					     tile->getTexture()->getSize().x, -(int)tile->getTexture()->getSize().y));
	}
      //ROT180
      if (this->_controller->randomBetween(0, 1) == 0)
	{
	  tile->setRotation(180);
	}
      this->_starsTiles.push_back(tile);
    }
}

void	RType::View::StarField::addBGTile(My::RenderWindow &w)
{
  if (this->_BGStarsTilesPool.empty())
    {
      for (int i = 0; i < 2; ++i)
	{
	  sf::Sprite *sprite = new sf::Sprite;
	  sf::Texture *tex;
	  if ((tex = this->_controller->resources.getTexture("BGStarsTile")))
	    {
	      sprite->setTexture(*tex);
	      sprite->setScale(Controller::Display::getScale(w));
	      sprite->setColor(sf::Color(255, 255, 255, 100));
	      this->_BGStarsTilesPool.push_back(sprite);
	    }
	}
    }
  if (this->_BGStarsTilesPool.empty() == false)
    {
      sf::Sprite *tile = this->_BGStarsTilesPool.back();
      this->_BGStarsTilesPool.pop_back();
      tile->setOrigin(tile->getLocalBounds().width / 2, tile->getLocalBounds().height / 2);
      tile->setPosition(w.getSize().x + tile->getGlobalBounds().width / 2, w.getSize().y / 2);
      tile->setRotation(0);
      //SPRITE RANDOMISATION
      //FLIPX
      if (this->_controller->randomBetween(0, 1) == 0)
	{
	  tile->setTextureRect(sf::Rect<int>(tile->getTexture()->getSize().x, 0,
					     -(int)tile->getTexture()->getSize().x, tile->getTexture()->getSize().y));
	}
      //FLIPY
      if (this->_controller->randomBetween(0, 1) == 0)
	{
	  tile->setTextureRect(sf::Rect<int>(0, tile->getTexture()->getSize().y,
					     tile->getTexture()->getSize().x, -(int)tile->getTexture()->getSize().y));
	}
      //ROT180
      if (this->_controller->randomBetween(0, 1) == 0)
	{
	  tile->setRotation(180);
	}
      this->_BGStarsTiles.push_back(tile);
    }
}

void	RType::View::StarField::tick(My::Clock &c, My::RenderWindow &w)
{
  //NORMAL STARS
  if (this->_starsTiles.empty())
    {
      this->addTile(w);
      while (this->_starsTiles.front()->getPosition().x + this->_starsTiles.back()->getGlobalBounds().width / 2 > 0)
	{
	  for (std::vector<sf::Sprite *>::iterator it = this->_starsTiles.begin();
	       it != this->_starsTiles.end();
	       ++it)
	    (*it)->move(-(*it)->getGlobalBounds().width, 0);
	  this->addTile(w);
	}
    }
  if (this->_starsTiles.empty() == false)
    {
      if (this->_starsTiles.back()->getPosition().x + this->_starsTiles.back()->getGlobalBounds().width / 2 <=
	  w.getSize().x)
	this->addTile(w);
    }
  for (std::vector<sf::Sprite *>::iterator it = this->_starsTiles.begin();
       it != this->_starsTiles.end();)
    {
      (*it)->move(-50 * c.getElapsedTime(), 0);
      if ((*it)->getPosition().x + this->_starsTiles.back()->getGlobalBounds().width / 2 < 0)
	{
	  this->_starsTilesPool.push_back(*it);
	  it = this->_starsTiles.erase(it);
	}
      else
	++it;
    }

  //BG STARS
  if (this->_BGStarsTiles.empty())
    {
      this->addBGTile(w);
      while (this->_BGStarsTiles.front()->getPosition().x + this->_BGStarsTiles.back()->getGlobalBounds().width / 2 > 0)
	{
	  for (std::vector<sf::Sprite *>::iterator it = this->_BGStarsTiles.begin();
	       it != this->_BGStarsTiles.end();
	       ++it)
	    (*it)->move(-(*it)->getGlobalBounds().width, 0);
	  this->addBGTile(w);
	}
    }
  if (this->_BGStarsTiles.empty() == false)
    {
      if (this->_BGStarsTiles.back()->getPosition().x + this->_BGStarsTiles.back()->getGlobalBounds().width / 2 <=
	  w.getSize().x)
	this->addBGTile(w);
    }
  for (std::vector<sf::Sprite *>::iterator it = this->_BGStarsTiles.begin();
       it != this->_BGStarsTiles.end();)
    {
      (*it)->move(-25 * c.getElapsedTime(), 0);
      if ((*it)->getPosition().x + this->_BGStarsTiles.back()->getGlobalBounds().width / 2 < 0)
	{
	  this->_BGStarsTilesPool.push_back(*it);
	  it = this->_BGStarsTiles.erase(it);
	}
      else
	++it;
    }
}

void	RType::View::StarField::draw(My::RenderWindow &w)
{
  for (std::vector<sf::Sprite *>::iterator it = this->_starsTiles.begin();
       it != this->_starsTiles.end();
       ++it)
      w.draw(*(*it));
  for (std::vector<sf::Sprite *>::iterator it = this->_BGStarsTiles.begin();
       it != this->_BGStarsTiles.end();
       ++it)
      w.draw(*(*it));
}

void	RType::View::StarField::unload(void)
{
}

int	RType::View::StarField::zIndex(void)
{
  return (0);
}

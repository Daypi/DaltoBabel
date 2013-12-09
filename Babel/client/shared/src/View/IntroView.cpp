//
// Intro.cpp for rtype in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Mon Oct 28 13:12:07 2013 martin lequeux-gruninger
// Last update Wed Nov 20 03:19:56 2013 martin lequeux-gruninger
//

#include	"View/Intro.hh"

void	RType::View::Intro::initialize(My::RenderWindow &w)
{
  sf::Texture *tex;

  if ((tex = this->_controller->resources.getTexture("introBG")))
    {
      this->_backgroundSprite.setTexture(*tex);
      this->_backgroundSprite.setScale(Controller::Display::getScale(w));
    }
  sf::Music *music;
  if ((music = this->_controller->resources.getMusic("opening")))
    {
      this->_controller->resources.getMusic("opening")->setLoop(true);
      this->_controller->resources.getMusic("opening")->play();
    }
  // this->_spaceship.initialize(w);
  // for (int i = 0; i < 200; ++i)
  //   {
  //     Bullet *bullet = new Bullet(this->_controller);
  //     bullet->initialize(w);
  //     this->_bulletsPool.push_back(bullet);
  //   }
  this->reset(w);
}

void	RType::View::Intro::reset(My::RenderWindow &w)
{
  this->_timeLeft = 3.0;
  w.setMouseCursorVisible(false);
  // this->_spaceship.getSprite().setOrigin(this->_spaceship.getSprite().getLocalBounds().width / 2,
  // 					 this->_spaceship.getSprite().getLocalBounds().height / 2);
  // this->_spaceship.setPosition(2 * - (float)this->_spaceship.getSprite().getGlobalBounds().width,
  // 			       w.getSize().y - 1.5 * (float)this->_spaceship.getSprite().getGlobalBounds().height);
  // this->_spaceship.setDirection(1, 0);
  // this->_spaceship.setSpeed(.5);
  // this->_canFire = true;
  // this->_spaceship.autoUpdate(true);
}

void	RType::View::Intro::update(My::Clock &, My::Event &, My::RenderWindow &)
{
  // if (this->_spaceship.visible())
  //   this->_spaceship.update(c, e, w);

  // std::vector<Bullet *>::iterator bulletsEnd = this->_bullets.end();
  // for (std::vector<Bullet *>::iterator it = this->_bullets.begin(); it != bulletsEnd; ++it)
  //   if ((*it)->visible())
  //     (*it)->update(c, e, w);
}

void	RType::View::Intro::guiEvent(My::Clock &, My::Callback &, My::RenderWindow &)
{
  // if (this->_spaceship.visible())
  //   this->_spaceship.update(c, e, w);

  // std::vector<Bullet *>::iterator bulletsEnd = this->_bullets.end();
  // for (std::vector<Bullet *>::iterator it = this->_bullets.begin(); it != bulletsEnd; ++it)
  //   if ((*it)->visible())
  //     (*it)->update(c, e, w);
}

void	RType::View::Intro::loadInterface(My::RenderWindow &)
{
}

void	RType::View::Intro::updateInterface(My::RenderWindow &)
{
}

void	RType::View::Intro::unloadInterface(My::RenderWindow &)
{
}

void	RType::View::Intro::tick(My::Clock &c, My::RenderWindow &w)
{
  this->_timeLeft -= c.getElapsedTime();
  if (this->_timeLeft <= 0)
    {
      this->visible(false, w);
      _controller->display.getDisplay(Controller::Display::MENU)->visible(true, w);
    }
  // if (this->_spaceship.visible())
  //   {
  //     this->_spaceship.tick(c, w);
  //     if (this->_spaceship.getPosition().x > w.getSize().x)
  // 	{
  // 	  this->visible(false, w);
  // 	  _controller->displayController.getDisplay(DisplayController::MENU)->visible(true, w);
  // 	}
  //   }

  // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->_canFire == true)
  //   {
  //     if (this->_bulletsPool.empty())
  // 	{
  // 	  for (int i = 0; i < 50; ++i)
  // 	    {
  // 	      Bullet *bullet = new Bullet(this->_controller);
  // 	      bullet->initialize(w);
  // 	      this->_bulletsPool.push_back(bullet);
  // 	    }
  // 	}
  //     if (this->_bulletsPool.empty() == false)
  // 	{
  // 	  this->_canFire = false;
  // 	  Bullet *bullet = this->_bulletsPool.back();
  // 	  this->_bulletsPool.pop_back();
  // 	  bullet->reset(w);
  // 	  bullet->getSprite().setOrigin(bullet->getSprite().getLocalBounds().width / 2,
  // 					bullet->getSprite().getLocalBounds().height / 2);
  // 	  bullet->setPosition((this->_spaceship.getPosition().x +
  // 			       this->_spaceship.getSprite().getGlobalBounds().width -
  // 			       bullet->getSprite().getGlobalBounds().width / 2)
  // 			      ,
  // 			      (this->_spaceship.getPosition().y +
  // 			       (this->_spaceship.getSprite().getGlobalBounds().height / 2) -
  // 			       bullet->getSprite().getGlobalBounds().height / 2));
  // 	  bullet->setSpeed(1);
  // 	  this->_bullets.push_back(bullet);
  // 	}
  //   }
  // else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->_canFire == false)
  //   this->_canFire = true;

  // for (std::vector<Bullet *>::iterator it = this->_bullets.begin(); it != this->_bullets.end();)
  //   {
  //     if ((*it)->visible())
  // 	(*it)->tick(c, w);
  //     if ((*it)->getPosition().x > w.getSize().x)
  // 	{
  // 	  this->_bulletsPool.push_back(*it);
  // 	  it = this->_bullets.erase(it);
  // 	}
  //     else
  // 	++it;
  //   }
}

void	RType::View::Intro::draw(My::RenderWindow &w)
{
  w.draw(this->_backgroundSprite);
  // if (this->_spaceship.visible())
  //   this->_spaceship.draw(w);

  // std::vector<Bullet *>::iterator bulletsEnd = this->_bullets.end();
  // for (std::vector<Bullet *>::iterator it = this->_bullets.begin(); it != bulletsEnd; ++it)
  //   if ((*it)->visible())
  //     (*it)->draw(w);
}

void	RType::View::Intro::unload(void)
{
}

int	RType::View::Intro::zIndex(void)
{
  return (1);
}

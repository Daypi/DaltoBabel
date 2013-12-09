//
// Game.cpp for rtype in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Mon Oct 28 13:12:07 2013 martin lequeux-gruninger
// Last update Sat Nov 16 14:01:00 2013 martin lequeux-gruninger
//

#include	"View/Game.hh"

void	RType::View::Game::initialize(My::RenderWindow &w)
{
  // this->_spaceship.initialize(w);
  // for (int i = 0; i < 200; ++i)
  //   {
  //     Bullet *bullet = new Bullet(this->_controller);
  //     bullet->initialize(w);
  //     this->_bulletsPool.push_back(bullet);
  //   }
  this->reset(w);
}

void	RType::View::Game::reset(My::RenderWindow &)
{
  // this->_spaceship.boundToScreen(true);
  // this->_spaceship.getSprite().setOrigin(this->_spaceship.getSprite().getLocalBounds().width / 2,
  // 					 this->_spaceship.getSprite().getLocalBounds().height / 2);
  // this->_spaceship.setPosition((float)this->_spaceship.getSprite().getGlobalBounds().width,
  // 			       w.getSize().y / 2);
}

void	RType::View::Game::update(My::Clock &, My::Event &, My::RenderWindow &)
{
  // if (this->_spaceship.visible())
  //   this->_spaceship.update(c, e, w);
}

void	RType::View::Game::guiEvent(My::Clock &, My::Callback &, My::RenderWindow &)
{
  // if (this->_spaceship.visible())
  //   this->_spaceship.update(c, e, w);
}

void	RType::View::Game::loadInterface(My::RenderWindow &)
{
}

void	RType::View::Game::updateInterface(My::RenderWindow &)
{
}

void	RType::View::Game::unloadInterface(My::RenderWindow &)
{
}

void	RType::View::Game::tick(My::Clock &, My::RenderWindow &)
{
  // if (this->_spaceship.visible())
  //   this->_spaceship.tick(c, w);

  // if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->_canFire == true)
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
  // else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->_canFire == false)
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

void	RType::View::Game::draw(My::RenderWindow &)
{
//   if (this->_spaceship.visible())
//     this->_spaceship.draw(w);
//   std::vector<Bullet *>::iterator bulletsEnd = this->_bullets.end();
//   for (std::vector<Bullet *>::iterator it = this->_bullets.begin(); it != bulletsEnd; ++it)
//     if ((*it)->visible())
//       (*it)->draw(w);
}

void	RType::View::Game::unload(void)
{
}

int	RType::View::Game::zIndex(void)
{
  return (0);
}

//
// TexturesController.hpp for rtype in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Tue Oct 29 09:27:15 2013 martin lequeux-gruninger
// Last update Wed Nov 20 03:17:21 2013 martin lequeux-gruninger
//

#pragma		once

#include	<iostream>
#include	<SFML/System.hpp>
#include	<SFML/Graphics.hpp>
#include	<SFML/Audio.hpp>
#include	<map>

namespace	RType
{
  class		Resources
  {
  private:
    Resources		&operator=(const Resources &);
    Resources(const Resources &);

    std::map<std::string, sf::Texture *>	_textures;
    std::map<std::string, sf::Music *>		_musics;
    std::map<std::string, sf::SoundBuffer *>	_sounds;
  public:
    Resources()
    {
      this->newTexture("introBG");
      this->newTexture("spaceship");
      this->newTexture("spaceshipRight");
      this->newTexture("spaceshipLeft");
      this->newTexture("spaceshipDown");
      this->newTexture("spaceshipUp");
      this->newTexture("optionsText");
      this->newTexture("playText");
      this->newTexture("selector");
      this->newTexture("starsTile");
      this->newTexture("BGStarsTile");
    }

    ~Resources() {
      for (std::map<std::string, sf::Music *>::iterator it = _musics.begin(); it != _musics.end();++it)
	delete ((*it).second);
    }

    //TEXTURES
    sf::Texture			*newTexture(const std::string &textureName,
					    bool smooth = true,
					    const std::string &path = "../shared/ressources/assets/",
					    const std::string &extension = "png")
    {
      std::string file = path + textureName + std::string(".") + extension;

      std::map<std::string, sf::Texture *>::iterator it	= this->_textures.find(file);

      //AVOID DUPLICATES
      if (it != this->_textures.end())
	return ((*it).second);
      else
	{
	  sf::Texture *tex = new sf::Texture;
	  if (tex && tex->loadFromFile(file) == false)
	    {
	      delete tex;
	      return (NULL);
	    }
	  tex->setSmooth(smooth);
	  this->_textures[file] = tex;
	  return (tex);
	}
    }

    sf::Texture			*getTexture(const std::string &textureName,
					    const std::string &path = "../shared/ressources/assets/",
					    const std::string &extension = "png")
    {
      return (newTexture(textureName, true, path, extension));
    }




    sf::Music			*newMusic(const std::string &fileName,
					  const std::string &path = "../shared/ressources/musics/",
					  const std::string &extension = "wav")
    {
      std::string file = path + fileName + std::string(".") + extension;

      std::map<std::string, sf::Music *>::iterator it = this->_musics.find(file);

      //AVOID DUPLICATES
      if (it != this->_musics.end())
	return ((*it).second);
      else
	{
	  sf::Music *music = new sf::Music;
	  if (music && !music->openFromFile(file))
	    {
	      delete music;
	      return (NULL);
	    }
	  this->_musics[file] = music;
	  return (music);
	}
    }

    sf::Music			*getMusic(const std::string &fileName,
					  const std::string &path = "../shared/ressources/musics/",
					  const std::string &extension = "wav")
    {
      return (newMusic(fileName, path, extension));
    }






    sf::SoundBuffer			*newSound(const std::string &fileName,
						  const std::string &path = "../shared/ressources/sounds/",
						  const std::string &extension = "ogg")
    {
      std::string file = path + fileName + std::string(".") + extension;

      std::map<std::string, sf::SoundBuffer *>::iterator it = this->_sounds.find(file);

      //AVOID DUPLICATES
      if (it != this->_sounds.end())
	return ((*it).second);
      else
	{
	  sf::SoundBuffer *buff = new sf::SoundBuffer;
	  if (buff && !buff->loadFromFile(file))
	    {
	      delete buff;
	      return (NULL);
	    }
	  this->_sounds[file] = buff;
	  return (buff);
	}
    }

    sf::SoundBuffer			*getSound(const std::string &fileName,
					  const std::string &path = "../shared/ressources/sounds/",
					  const std::string &extension = "ogg")
    {
      return (newSound(fileName, path, extension));
    }
  };
}

//
// Room.cpp for rtype in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Mon Oct 28 13:12:07 2013 martin lequeux-gruninger
// Last update Sun Nov 24 21:30:38 2013 martin lequeux-gruninger
//

#include	"View/Room.hh"
#include	"Util.hpp"

void	RType::View::Room::initialize(My::RenderWindow &w)
{
	this->reset(w);
}

void	RType::View::Room::reset(My::RenderWindow &w)
{
	w.setMouseCursorVisible(true);
}

void	RType::View::Room::update(My::Clock &, My::Event &, My::RenderWindow &)
{
}

void	RType::View::Room::guiEvent(My::Clock &, My::Callback &c, My::RenderWindow &)
{
	if (c.callbackID == 1) // exit
	{
		if (c.trigger == tgui::Callback::mouseClick)
		{
			if (this->_controller->display.getVisibleDisplay() == RType::Controller::Display::ROOM)
			{
				this->_controller->display.setDisplay(RType::Controller::Display::ROOM, false);
				this->_controller->display.setDisplay(RType::Controller::Display::LOBBY, true);
				this->_controller->display.getDisplay(this->_controller->display.getVisibleDisplay())->updateInterface(*this->_controller->display.getWindow());
			}
			this->_controller->model.lobby.getActualRoom()->quit();
			this->_controller->model.lobby.setActualRoom(NULL);
		}
	}
	if (c.callbackID == 2) // start
	{
		if (c.trigger == tgui::Callback::mouseClick)
		{
			this->_controller->model.lobby.getActualRoom()->start();
			if (this->_controller->display.getVisibleDisplay() == RType::Controller::Display::ROOM)
			{
				this->_controller->display.setDisplay(RType::Controller::Display::ROOM, false);
				this->_controller->display.setDisplay(RType::Controller::Display::GAME, true);
				this->_controller->display.getDisplay(this->_controller->display.getVisibleDisplay())->updateInterface(*this->_controller->display.getWindow());
			}
		}
	}
	if (c.callbackID == 3) // ready
	{
		if (c.trigger == tgui::Callback::mouseClick)
		{
		}
	}
	if (c.callbackID == 4) // chat
	{
		if (c.trigger == tgui::Callback::mouseClick)
		{
			std::string msg = msgChat->getText();
			this->_controller->model.lobby.getActualRoom()->chat(msg);
			msgChat->setText("");
		}
	}
}

void	RType::View::Room::loadInterface(My::RenderWindow &w)
{
	unsigned int	x(w.getSize().x);
	unsigned int	y(w.getSize().y);

	w.removeAllObjects(); // bof comme moyen mais j'ai pas réussis a trouver ce qu'il se passait

	players = w.add<tgui::Label>();
	players->setText("PLAYERS");
	players->setTextSize(y / 40 * 3);
	players->setPosition(x / 40, y / 40);
	players->setTextColor(sf::Color::White);

	playerList = w.add<tgui::ListBox>();
	playerList->load(x / 3 * 2 - x / 40, y / 3 * 2 - y / 40 * 6, "./../shared/ressources/TGUI/objects/Scrollbar/White", 50);
	playerList->setBorders(4, 4, 4, 4);
	playerList->setPosition(x / 40, y / 40 * 6);
	playerList->addItem("PLAYERS");
	playerList->changeColors(sf::Color(0, 0, 0, 0),  // Background color
		sf::Color(190, 190, 190),  // Text color
		sf::Color(128, 128, 128, 128),  // Background color of the selected item.
		sf::Color(255, 255, 255),  // Selected Text color
		sf::Color(255, 255, 255, 10));  // Border color

	rightSideUp = w.add<tgui::Panel>("first panel");
	rightSideUp->load(x / 3 - x / 20, y / 20 * 2, sf::Color(255, 255, 255, 10));
	rightSideUp->setPosition(x / 3 * 2 + x / 40, y / 40);

	rightSide = w.add<tgui::Panel>("first panel");
	rightSide->load(x / 3 - x / 20, y / 20 * 14, sf::Color(255, 255, 255, 10));
	rightSide->setPosition(x / 3 * 2 + x / 40, y / 40 * 6);

	rightSideDown = w.add<tgui::Panel>("first panel");
	rightSideDown->load(x / 3 - x / 20, y / 20 * 2, sf::Color(255, 255, 255, 10));
	rightSideDown->setPosition(x / 3 * 2 + x / 40, y / 40 * 35);

	chatList = w.add<tgui::ListBox>();
	chatList->load(x / 3 * 2 - x / 40, y / 3 - (y / 40 * 5), "./../shared/ressources/TGUI/objects/Scrollbar/White", 15);
	chatList->setBorders(4, 4, 4, 4);
	chatList->setPosition(x / 40, y / 40 * 28);
	chatList->addItem("CHAT");
	chatList->changeColors(sf::Color(0, 0, 0, 0),  // Background color
		sf::Color(190, 190, 190),  // Text color
		sf::Color(0, 0, 0, 0),  // Background color of the selected item.
		sf::Color(255, 255, 255),  // Selected Text color
		sf::Color(255, 255, 255, 10));  // Border color

	leftSide = w.add<tgui::Panel>("first panel");
	leftSide->load(x / 3 * 2 - x / 40, y / 40 * 3, sf::Color(255, 255, 255, 10));
	leftSide->setPosition(x / 40, y - y / 40 - leftSide->getSize().y);

	exit = w.add<tgui::Button>();
	exit->load("./../shared/ressources/TGUI/objects/Button/White");
	exit->setText("EXIT");
	exit->setSize(x / 3 - x / 40 * 4, y / 20);
	exit->setPosition(x / 3 * 2 + x / 40 * 2, y / 40 * 2);
	exit->setTextColor(sf::Color::White);
	exit->callbackID = 1;

	room = w.add<tgui::Label>();
	room->setText("Room Attribute");
	room->setTextSize(y / 40 * 2);
	room->setPosition(x / 3 * 2 + x / 40 * 2, y / 40 * 7);
	room->setTextColor(sf::Color::White);

	roomName = w.add<tgui::Label>();
	roomName->setSize(x / 3 - (x / 40) * 4, y / 20);
	roomName->setPosition(x / 3 * 2 + x / 40 * 2, y / 40 * 11);
	roomName->setTextSize(y / 40 * 1);
	roomName->setText("Name : " + this->_controller->model.lobby.getActualRoom()->getName());
	roomName->setTextColor(sf::Color::White);

	maxPlayer = w.add<tgui::Label>();
	maxPlayer->setText("Players Max : " + Util::toString<int>(this->_controller->model.lobby.getActualRoom()->getMaxPlayer()));
	maxPlayer->setTextSize(y / 40 * 1);
	maxPlayer->setPosition(x / 3 * 2 + x / 40 * 2, y / 40 * 20);
	maxPlayer->setTextColor(sf::Color::White);

	level = w.add<tgui::Label>();
	level->setText("Level : " + this->_controller->model.lobby.getActualRoom()->getLevel());
	level->setTextSize(y / 40 * 1);
	level->setPosition(x / 3 * 2 + x / 40 * 2, y / 40 * 15);
	level->setTextColor(sf::Color::White);

	std::string tmp(this->_controller->model.lobby.getActualRoom()->getSpectate() ? "YES" : "NO");
	spectate = w.add<tgui::Label>();
	spectate->setText("Spectator allowed : " + tmp);
	spectate->setTextSize(y / 40 * 1);
	spectate->setPosition(x / 3 * 2 + x / 40 * 2, y / 40 * 25);
	spectate->setTextColor(sf::Color::White);

	start = w.add<tgui::Button>();
	start->load("./../shared/ressources/TGUI/objects/Button/White");
	start->setText("START");
	start->setSize(x / 3 - x / 40 * 4, y / 20);
	start->setPosition(x / 3 * 2 + x / 40 * 2, y / 40 * 31);
	start->callbackID = 2;

	ready = w.add<tgui::Button>();
	ready->load("./../shared/ressources/TGUI/objects/Button/White");
	ready->setText("READY");
	ready->setSize(x / 3 - x / 40 * 4, y / 20);
	ready->setPosition(x / 3 * 2 + x / 40 * 2, y / 40 * 36);
	ready->callbackID = 3;

	msgChat = w.add<tgui::EditBox>();
	msgChat->load("./../shared/ressources/TGUI/objects/EditBox/White");
	msgChat->setBorders(6, 4, 6, 4);
	msgChat->setSize(leftSide->getSize().x / 10 * 8, leftSide->getSize().y / 2);
	msgChat->setPosition(leftSide->getPosition().x + leftSide->getSize().x / 20, leftSide->getPosition().y + leftSide->getSize().y / 4);

	send = w.add<tgui::Button>();
	send->load("./../shared/ressources/TGUI/objects/Button/White");
	send->setText("SEND");
	send->setSize(leftSide->getSize().x / 10 * 1, leftSide->getSize().y / 2);
	send->setPosition(msgChat->getPosition().x + msgChat->getSize().x, leftSide->getPosition().y + leftSide->getSize().y / 4);
	send->callbackID = 4;
}

void	RType::View::Room::updateInterface(My::RenderWindow &)
{
	std::vector<RType::Model::Player *>	tmpPlayer(this->_controller->model.lobby.getActualRoom()->getPlayers());
	std::vector<std::string>			tmpChat(this->_controller->model.lobby.getActualRoom()->getChat());

	playerList->removeAllItems();
	for (int i = 0; i < (int)tmpPlayer.size(); ++i)
	{
		playerList->addItem(Util::toString<int>(tmpPlayer[i]->getId()) + " - " + tmpPlayer[i]->getName());
	}

	chatList->removeAllItems();
	for (int i = 0; i < (int)tmpChat.size(); ++i)
	{
		chatList->addItem(tmpChat[i]);
	}
}

void	RType::View::Room::unloadInterface(My::RenderWindow &w)
{
	w.removeAllObjects();
}

void	RType::View::Room::tick(My::Clock &, My::RenderWindow &)
{
}

void	RType::View::Room::draw(My::RenderWindow &)
{
}

void	RType::View::Room::unload(void)
{
}

int	RType::View::Room::zIndex(void)
{
  return (3);
}

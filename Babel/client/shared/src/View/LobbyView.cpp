//
// Lobby.cpp for rtype in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Mon Oct 28 13:12:07 2013 martin lequeux-gruninger
// Last update Sun Nov 24 21:28:31 2013 martin lequeux-gruninger
//

#include	"View/Lobby.hh"
#include	"Util.hpp"

void	RType::View::Lobby::initialize(My::RenderWindow &w)
{
  this->reset(w);
}

void	RType::View::Lobby::reset(My::RenderWindow &w)
{
  w.setMouseCursorVisible(true);
}

void	RType::View::Lobby::update(My::Clock &, My::Event &, My::RenderWindow &)
{
}

void	RType::View::Lobby::guiEvent(My::Clock &, My::Callback &c, My::RenderWindow &)
{
	if (c.callbackID == 1) // back
	{
		if (c.trigger == tgui::Callback::mouseClick)
		{
			if (this->_controller->display.getVisibleDisplay() == RType::Controller::Display::LOBBY)
			{
				this->_controller->network.setInit(false);
				this->_controller->display.setDisplay(RType::Controller::Display::LOBBY, false);
				this->_controller->display.setDisplay(RType::Controller::Display::MENU, true);
				this->_controller->display.getDisplay(this->_controller->display.getVisibleDisplay())->unloadInterface(*this->_controller->display.getWindow());
			}
		}
	}
	if (c.callbackID == 2) // login
	{
		if (c.trigger == tgui::Callback::mouseClick)
		{
			std::string login = name->getText();
			this->_controller->model.lobby.login(login);
		}
	}
	if (c.callbackID == 3) // create
	{
		if (c.trigger == tgui::Callback::mouseClick)
		{
			if (name->getTextSize() != 0 && roomName->getTextSize() != 0)
				this->_controller->model.lobby.create(spectate->isChecked(), Util::fromString<int>(listPLayers->getSelectedItem()), name->getText(), roomName->getText(), listLevel->getSelectedItem());
		}
	}
	if (c.callbackID == 4) // join
	{
		if (c.trigger == tgui::Callback::mouseClick)
		{
			std::string		tmpName;

			tmpName = roomList->getSelectedItem();
			tmpName = tmpName.substr(0, tmpName.find(' '));
			if (this->_controller->model.lobby.getActualRoom() == NULL && this->_controller->model.lobby.getRooms().size() > 0)
				this->_controller->model.lobby.getRooms()[0]->join(0, Util::fromString<short>(tmpName), name->getText());
			else if (this->_controller->model.lobby.getActualRoom())
				this->_controller->model.lobby.getActualRoom()->join(0, Util::fromString<short>(tmpName), name->getText());
		}
	}
	if (c.callbackID == 5) // chat
	{
		if (c.trigger == tgui::Callback::mouseClick)
		{
			std::string msg = msgChat->getText();
			this->_controller->model.lobby.chat(msg);
			msgChat->setText("");
		}
	}
}

void	RType::View::Lobby::loadInterface(My::RenderWindow &w)
{
  unsigned int	x(w.getSize().x);
  unsigned int	y(w.getSize().y);

  w.removeAllObjects(); // bof comme moyen mais j'ai pas réussis a trouver ce qu'il se passait

  back = w.add<tgui::Button>();
  back->load("./../shared/ressources/TGUI/objects/Button/White");
  back->setText("BACK");
  back->setSize(x / 3 - x / 40 * 10, y / 20);
  back->setPosition(x / 40, y / 40 * 2);
  back->callbackID = 1;

  rooms = w.add<tgui::Label>();
  rooms->setText("ROOMS");
  rooms->setTextSize(y / 40 * 3);
  rooms->setPosition(x / 40 * 5, y / 40);
  rooms->setTextColor(sf::Color::White);

  roomList = w.add<tgui::ListBox>("roomList");
  roomList->load(x / 3 * 2 - x / 40, y / 3 * 2 - y / 40 * 6, "./../shared/ressources/TGUI/objects/Scrollbar/White", 20);
  roomList->setBorders(4, 4, 4, 4);
  roomList->setPosition(x / 40, y / 40 * 6);
  roomList->addItem("Game list");
  roomList->changeColors(sf::Color(0, 0, 0, 0),  // Background color
			 sf::Color(190, 190, 190),  // Text color
			 sf::Color(128, 128, 128, 128),  // Background color of the selected item.
			 sf::Color(255, 255, 255),  // Selected Text color
			 sf::Color(255, 255, 255, 10));  // Border color

  rightSideUp = w.add<tgui::Panel>("rightSideUp");
  rightSideUp->load(x / 3 - x / 20, y / 20 * 2, sf::Color(255, 255, 255, 10));
  rightSideUp->setPosition(x / 3 * 2 + x / 40, y / 40);

  rightSide = w.add<tgui::Panel>("rightSide");
  rightSide->load(x / 3 - x / 20, y / 20 * 14, sf::Color(255, 255, 255, 10));
  rightSide->setPosition(x / 3 * 2 + x / 40, y / 40 * 6);

  rightSideDown = w.add<tgui::Panel>("rightSideDown");
  rightSideDown->load(x / 3 - x / 20, y / 20 * 2, sf::Color(255, 255, 255, 10));
  rightSideDown->setPosition(x / 3 * 2 + x / 40, y / 40 * 35);

  chatList = w.add<tgui::ListBox>("chatList");
  chatList->load(x / 3 * 2 - x / 40, y / 3 - (y / 40 * 5), "./../shared/ressources/TGUI/objects/Scrollbar/White", 15);
  chatList->setBorders(4, 4, 4, 4);
  chatList->setPosition(x / 40, y / 40 * 28);
  chatList->addItem("Ici c'est le chat.");
  chatList->changeColors(sf::Color(0, 0, 0, 0),  // Background color
			 sf::Color(190, 190, 190),  // Text color
			 sf::Color(0, 0, 0, 0),  // Background color of the selected item.
			 sf::Color(255, 255, 255),  // Selected Text color
			 sf::Color(255, 255, 255, 10));  // Border color

  leftSide = w.add<tgui::Panel>("leftSide");
  leftSide->load(x / 3 * 2 - x / 40, y / 40 * 3, sf::Color(255, 255, 255, 10));
  leftSide->setPosition(x / 40, y - y / 40 - leftSide->getSize().y);

  name = w.add<tgui::EditBox>("name");
  name->load("./../shared/ressources/TGUI/objects/EditBox/White");
  name->setBorders(6, 4, 6, 4);
  name->setSize(x / 3 - (x / 40) * 6, y / 20);
  name->setPosition(x / 3 * 2 + x / 40 * 2, y / 40 * 2);
  name->setText("Login");

  ok = w.add<tgui::Button>("ok");
  ok->load("./../shared/ressources/TGUI/objects/Button/White");
  ok->setText("OK");
  ok->setSize(x / 18, y / 20);
  ok->setPosition(name->getPosition().x + name->getSize().x, y / 40 * 2);
  ok->callbackID = 2;

  room = w.add<tgui::Label>("room");
  room->setText("Room Creation");
  room->setTextSize(y / 40 * 2);
  room->setPosition(x / 3 * 2 + x / 40 * 2, y / 40 * 7);
  room->setTextColor(sf::Color::White);

  roomName = w.add<tgui::EditBox>("roomName");
  roomName->load("./../shared/ressources/TGUI/objects/EditBox/White");
  roomName->setBorders(6, 4, 6, 4);
  roomName->setSize(x / 3 - (x / 40) * 4, y / 20);
  roomName->setPosition(x / 3 * 2 + x / 40 * 2, y / 40 * 11);
  roomName->setText("Room Name");

  spectate = w.add<tgui::Checkbox>("spectate");
  spectate->load("./../shared/ressources/TGUI/objects/Checkbox/White");
  spectate->setText("	Spectate");
  spectate->setTextSize(y / 40 * 1.5);
  spectate->setSize(y/20, y / 20);
  spectate->setPosition(x / 3 * 2 + x / 40 * 2, y / 40 * 25);
  spectate->check();

  maxPlayer = w.add<tgui::Label>("maxPlayer");
  maxPlayer->setText("Maximum Players");
  maxPlayer->setTextSize(y / 40 * 1.5);
  maxPlayer->setPosition(x / 3 * 2 + x / 40 * 2, y / 40 * 19);
  maxPlayer->setTextColor(sf::Color::White);

  listPLayers = w.add<tgui::ComboBox>("listPlayer");
  listPLayers->load("./../shared/ressources/TGUI/objects/ComboBox/White", x / 3 - x / 40 * 4, y / 40 * 2);
  listPLayers->setBorders(4, 4, 4, 4);
  listPLayers->setPosition(x / 3 * 2 + x / 40 * 2, y / 40 * 21);
  listPLayers->addItem("1");
  listPLayers->addItem("2");
  listPLayers->addItem("3");
  listPLayers->addItem("4");
  listPLayers->setSelectedItem(4);
  listPLayers->changeColors(sf::Color(0, 0, 0, 0),  // Background color
			    sf::Color(190, 190, 190),  // Text color
			    sf::Color(0, 0, 0, 0),  // Background color of the selected item.
			    sf::Color(255, 255, 255),  // Selected Text color
			    sf::Color(25, 25, 25, 255));  // Border color

  level = w.add<tgui::Label>("level");
  level->setText("Level");
  level->setTextSize(y / 40 * 1.5);
  level->setPosition(x / 3 * 2 + x / 40 * 2, y / 40 * 14);
  level->setTextColor(sf::Color::White);

  listLevel = w.add<tgui::ComboBox>("listLevel");
  listLevel->load("./../shared/ressources/TGUI/objects/ComboBox/White", x / 3 - x / 40 * 4, y / 40 * 2);
  listLevel->setBorders(4, 4, 4, 4);
  listLevel->setPosition(x / 3 * 2 + x / 40 * 2, y / 40 * 16);
  listLevel->addItem("Easy");
  listLevel->addItem("Medium");
  listLevel->addItem("H4RDC0R3");
  listLevel->setSelectedItem(2);
  listLevel->changeColors(sf::Color(0, 0, 0, 0),  // Background color
			  sf::Color(190, 190, 190),  // Text color
			  sf::Color(0, 0, 0, 0),  // Background color of the selected item.
			  sf::Color(255, 255, 255),  // Selected Text color
			  sf::Color(25, 25, 25, 255));  // Border color

  create = w.add<tgui::Button>("create");
  create->load("./../shared/ressources/TGUI/objects/Button/White");
  create->setText("CREATE");
  create->setSize(x / 3 - x / 40 * 4, y / 20);
  create->setPosition(x / 3 * 2 + x / 40 * 2, y / 40 * 31);
  create->callbackID = 3;

  join = w.add<tgui::Button>("join");
  join->load("./../shared/ressources/TGUI/objects/Button/White");
  join->setText("JOIN");
  join->setSize(x / 3 - x / 40 * 4, y / 20);
  join->setPosition(x / 3 * 2 + x / 40 * 2, y / 40 * 36);
  join->callbackID = 4;

  msgChat = w.add<tgui::EditBox>("msgChat");
  msgChat->load("./../shared/ressources/TGUI/objects/EditBox/White");
  msgChat->setBorders(6, 4, 6, 4);
  msgChat->setSize(leftSide->getSize().x / 10 * 8, leftSide->getSize().y / 2);
  msgChat->setPosition(leftSide->getPosition().x + leftSide->getSize().x / 20, leftSide->getPosition().y + leftSide->getSize().y / 4);

  send = w.add<tgui::Button>("send");
  send->load("./../shared/ressources/TGUI/objects/Button/White");
  send->setText("SEND");
  send->setSize(leftSide->getSize().x / 10 * 1, leftSide->getSize().y / 2);
  send->setPosition(msgChat->getPosition().x + msgChat->getSize().x, leftSide->getPosition().y + leftSide->getSize().y / 4);
  send->callbackID = 5;
}

void	RType::View::Lobby::updateInterface(My::RenderWindow &)
{
	std::vector<RType::Model::Room *>	list(this->_controller->model.lobby.getRooms());
	std::vector<std::string>			tmpChat(this->_controller->model.lobby.getChat());
	std::vector<std::string>			tmpLevels(this->_controller->model.lobby.getLevels());

	// NAME
	name->setText(this->_controller->model.lobby.getLogin());

	// ROOM LIST
	roomList->removeAllItems();
	for (int i = 0; i < (int)list.size(); ++i)
	{
		roomList->addItem(Util::toString<int>(list[i]->getRoomId()) + " - " + list[i]->getName() + "\t From : " + list[i]->getLogin() + "\t Level : " + list[i]->getLevel() + " \t Maximum Player : " + Util::toString(list[i]->getMaxPlayer()));
	}

	// CHAT LIST
	chatList->removeAllItems();
	for (int i = 0; i <  (int)tmpChat.size(); ++i)
	{
		chatList->addItem(tmpChat[i]);
	}

	// LEVEL LIST
	listLevel->removeAllItems();
	for (int i = 0; i <  (int)tmpLevels.size(); ++i)
	{
		listLevel->addItem(tmpLevels[i]);
	}
	listLevel->setSelectedItem(1);

	std::cout << "UPDATE" << std::endl;
}

void	RType::View::Lobby::unloadInterface(My::RenderWindow &w)
{
	w.removeAllObjects();
}

void	RType::View::Lobby::tick(My::Clock &, My::RenderWindow &)
{
}

void	RType::View::Lobby::draw(My::RenderWindow &)
{
}

void	RType::View::Lobby::unload(void)
{
}

int	RType::View::Lobby::zIndex(void)
{
  return (3);
}

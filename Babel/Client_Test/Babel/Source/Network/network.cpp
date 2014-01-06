#include "Include/Network/network.h"
#include "Include/Network/Util.hpp"

Network::Network(MyContactModel *model)
    :   _model(model)
{
    _sockUDP = NULL;
    this->_currentClient = false;
    _sockUDPServ = NULL;
    this->_currentServ = false;
    this->_idCall = 0;
    _sockTCP = NULL;
    _init = false;
    _handshake = false;
    _log = false;
    _reqUID = 0;
}

Network::~Network()
{
}

void	Network::setInit(bool b)
{
    _init = b;
}

void	Network::connect(const std::string &ip, int port)
{
    if (_init == false)
    {
        this->_sockUDP = new SocketClientUDP;

        try
        {
            this->_sockUDP->init(port, ip.c_str());
        }
        catch (Exception &e)
        {
            delete _sockUDP;
            _sockUDP = NULL;
            _init = false;
            throw Exception(e);
        }

        this->_sockUDPServ = new SocketServerUDP;
        try
        {
            this->_sockUDPServ->init(1337);
        }
        catch (Exception &e)
        {
            delete _sockUDPServ;
            _sockUDPServ = NULL;
            _init = false;
            throw Exception(e);
        }

        this->_sockTCP = new SocketClientTCP;
        try
        {
            this->_sockTCP->init(port, ip.c_str());
        }
        catch (Exception &e)
        {
            delete _sockTCP;
            _sockTCP = NULL;
            _init = false;
            throw Exception(e);
        }
        _init = true;
    }
}

void	Network::handlePackets()
{
    Packet  *packet;

    while ((packet = this->_factory.getPacket()))
    {
        packet->show();
        std::cout << "After show, before the good function" << std::endl;
        if (packet->getInstruction() == Packet::HANDSHAKE)
            this->sendHandshake();
        else if (packet->getInstruction() == Packet::LOGIN || packet->getInstruction() == Packet::CREATE_ACCOUNT)
            this->checkLogin(packet);
        else if (packet->getInstruction() == Packet::STATUSTEXT)
            this->refreshStatusText(packet);
        else if (packet->getInstruction() == Packet::STATUS)
            this->refreshStatus(packet);
        else if (packet->getInstruction() == Packet::LIST)
            this->refreshList(packet);
        else if (packet->getInstruction() == Packet::ADD_CONTACT)
            this->refreshAdd(packet);
        else if (packet->getInstruction() == Packet::REMOVE_CONTACT)
            this->refreshRm(packet);
        else if (packet->getInstruction() == Packet::BLOCK_CONTACT)
            this->refreshBlock(packet);
        else if (packet->getInstruction() == Packet::CALL)
            this->handleCall(packet);
        else if (packet->getInstruction() == Packet::HANGUP)
            this->closeCall(packet);
        else if (packet->getInstruction() == Packet::ACCEPT_CALL)
            this->acceptCall(packet);
        else if (packet->getInstruction() == Packet::REJECT_CALL)
            this->rejectCall(packet);
        else if (packet->getInstruction() == Packet::CHAT)
            this->receiveChat(packet);
        else
        {
            std::cout << "PACKET NON GERE" << std::endl;
            packet->show();
        }
        std::cout << "After the good function" << std::endl;
    }
}

void	Network::handleNetwork()
{
    if (_init)
    {
        try
        {
            handleNetworkUDP();
            handleNetworkUDPServ();
            handleNetworkTCP();
            handlePackets();
        }
        catch (Exception &e)
        {
            throw Exception(e);
        }
    }
}

void	Network::pushTCP(Packet *packet)
{
    this->_sendQueueTCP.push(packet);
}

void	Network::handleNetworkUDP()
{
    if (_sendQueueUDP.empty() == false && _sockUDP->isWritable())
    {
        this->_currentClient = true;
        this->_currentServ = false;
        std::pair<unsigned char *, int> *tmp = this->_sendQueueUDP.front();
        this->_sendQueueUDP.pop();
        try
        {
            _sockUDP->send(reinterpret_cast<char *>(tmp->first), tmp->second);
        }
        catch (Exception &e)
        {
            delete _sockUDP;
            _sockUDP = NULL;
            _init = false;
            throw Exception(e);
        }
        delete tmp;
    }
    if (_sockUDP->isReadable())
    {
        this->_currentClient = true;
        this->_currentServ = false;
        char buffer[4098];
        int rdSize;

        try
        {
            _sockUDP->recv(buffer, 4096, &rdSize);
        }
        catch (Exception &e)
        {
            delete _sockUDP;
            _sockUDP = NULL;
            _init = false;
            throw Exception(e);
        }
       this->_model->play(reinterpret_cast<const unsigned char *>(buffer), rdSize);
    }
}

void	Network::handleNetworkUDPServ()
{
    if (_sendQueueUDPServ.empty() == false && _sockUDPServ->isWritable().size() == 1 && this->_idCall != 0)
    {
        this->_currentServ = true;
        this->_currentClient = false;
        std::pair<unsigned char *, int> *tmp = this->_sendQueueUDPServ.front();
        this->_sendQueueUDPServ.pop();
        try
        {
            _sockUDPServ->send(this->_idCall, reinterpret_cast<char *>(tmp->first), tmp->second);
        }
        catch (Exception &e)
        {
            delete _sockUDPServ;
            _sockUDPServ = NULL;
            _init = false;
            this->_idCall = 0;
            throw Exception(e);
        }
        delete tmp;
    }
    if (_sockUDPServ->isReadable().size() == 1)
    {
        int rdSize = 0;
        std::map<unsigned int, std::pair<const char *, int> >   map;

        this->_currentServ = true;
        this->_currentClient = false;
        try
        {
            map = _sockUDPServ->recv(4096);
            for (std::map<unsigned int, std::pair<const char *, int> >::iterator it = map.begin(); it != map.end(); ++it)
            {
                this->_idCall = (*it).first;
                rdSize = (*it).second.second;
                this->_model->play(reinterpret_cast<const unsigned char *>((*it).second.first), rdSize);
            }
        }
        catch (const Exception &e)
        {
            delete _sockUDPServ;
            _sockUDPServ = NULL;
            _init = false;
            this->_idCall = 0;
            throw Exception(e);
        }
    }
}
void	Network::handleNetworkTCP()
{
    if (_sendQueueTCP.empty() == false && _sockTCP->isWritable())
    {
        Packet	*packet = this->_sendQueueTCP.front();
        this->_sendQueueTCP.pop();
        try
        {
            _sockTCP->send(packet->serialize(), packet->size());
        }
        catch (Exception &e)
        {
            delete _sockTCP;
            _sockTCP = NULL;
            _init = false;
            throw Exception(e);
        }
        delete packet;
    }
    if (_sockTCP->isReadable())
    {
        char buffer[4096];
        int rdSize;

        try
        {
            _sockTCP->recv(buffer, 4096, &rdSize);
        }
        catch (Exception &e)
        {
            delete _sockTCP;
            _sockTCP = NULL;
            _init = false;
            throw Exception(e);
        }
        std::cout << "Data packet factory = push buff in factory" << std::endl;
        for (unsigned int i = 0; i < (unsigned int)rdSize; ++i)
        {
            std::cout << Util::format('0', 2, Util::toHex<unsigned int>((unsigned char)buffer[i])) << " ";
        }
        std::cout << std::endl;
        _factory.feed(buffer, rdSize);
    }
}

void    Network::sendHandshake()
{
    this->_sendQueueTCP.push(new Packet(this->getUID(), Packet::HANDSHAKE));
    this->_handshake = true;
}


void    Network::sendLogin(bool isNewUser, const std::string &login, const std::string &mdp)
{
    Packet  *pack = new Packet(this->getUID(), isNewUser == true ? Packet::CREATE_ACCOUNT : Packet::LOGIN);

    std::cout << "Le mot de passe = " << mdp << std::endl;
    pack->setFormat("ss");
    pack->updateData(4 + login.size() + 4 + mdp.size());
    pack->appendToData(0, login);
    pack->appendToData(1, mdp);
    this->_sendQueueTCP.push(pack);
    this->_handshake = false;
}

void    Network::sendStatusText(const std::string& newStat)
{
    Packet  *pack = new Packet(this->getUID(), Packet::STATUSTEXT);

    pack->setFormat("s");
    pack->updateData(4 + newStat.size());
    pack->appendToData(0, newStat);
    this->_sendQueueTCP.push(pack);
}

void    Network::sendStatus(eStatus status)
{
    Packet  *pack = new Packet(this->getUID(), Packet::STATUS);

    pack->setFormat("c");
    pack->updateData(3);
    pack->appendToData(0, status);
    this->_sendQueueTCP.push(pack);
}

void    Network::sendMsg(const std::string& login, const std::string& msg)
{
    Packet  *pack = new Packet(this->getUID(), Packet::CHAT);

    pack->setFormat("ss");
    pack->updateData(4 + login.size() + 4 + msg.size());
    pack->appendToData(0, login);
    pack->appendToData(1, msg);
    pack->show();
    this->_sendQueueTCP.push(pack);
}

void    Network::addContact(const std::string& name)
{
    Packet  *pack = new Packet(this->getUID(), Packet::ADD_CONTACT);

    pack->setFormat("s");
    pack->updateData(4 + name.size());
    pack->appendToData(0, name);
    this->_sendQueueTCP.push(pack);
    this->sendList();
}

void    Network::rmContact(const std::string& name)
{
    Packet  *pack = new Packet(this->getUID(), Packet::REMOVE_CONTACT);

    pack->setFormat("s");
    pack->updateData(4 + name.size());
    pack->appendToData(0, name);
    this->_sendQueueTCP.push(pack);
    this->sendList();
}

void    Network::blockContact(const std::string& name)
{
    Packet  *pack = new Packet(this->getUID(), Packet::BLOCK_CONTACT);

    pack->setFormat("s");
    pack->updateData(4 + name.size());
    pack->appendToData(0, name);
    this->_sendQueueTCP.push(pack);
    this->sendList();
}

void    Network::sendAccept(const std::string& login)
{
    Packet  *pack = new Packet(this->getUID(), Packet::ACCEPT_CALL);

    pack->setFormat("s");
    pack->updateData(4 + login.size());
    pack->appendToData(0, login);
    this->_sendQueueTCP.push(pack);
    this->_currentServ = true;
    this->_model->openChat(login);
    this->_model->setPlayback(true);
}

void    Network::sendReject(const std::string& login)
{
    Packet  *pack = new Packet(this->getUID(), Packet::REJECT_CALL);

    pack->setFormat("s");
    pack->updateData(4 + login.size());
    pack->appendToData(0, login);
    this->_sendQueueTCP.push(pack);
}

void    Network::sendList()
{
    this->_sendQueueTCP.push(new Packet(this->getUID(), Packet::LIST));
}

void    Network::sendCall(const std::string& login)
{
    Packet  *pack = new Packet(this->getUID(), Packet::CALL);

    pack->setFormat("s");
    pack->updateData(4 + login.size());
    pack->appendToData(0, login);
    this->_sendQueueTCP.push(pack);
}

void    Network::sendHangUp()
{
    this->_sendQueueTCP.push(new Packet(this->getUID(), Packet::HANGUP));
    this->_model->closeCall();
    if (this->_currentServ)
        this->_sockUDPServ->closeClients();
}

void    Network::sendPing()
{
    this->_sendQueueTCP.push(new Packet(this->getUID(), Packet::PING));
}

void    Network::sendDial(unsigned char *buff, int size)
{
    std::pair<unsigned char *, int> *tmp = new std::pair<unsigned char *, int>(buff, size);
    if (this->_currentServ)
        this->_sendQueueUDPServ.push(tmp);
    else
        this->_sendQueueUDP.push(tmp);
}

void    Network::checkLogin(Packet *packet)
{
    if (packet->getChar(0) != 1)
    {
        std::cout << packet->getString(1) << std::endl;
        return;
    }
    this->_log = true;
}

void    Network::refreshStatusText(Packet *packet)
{
    if (packet->getChar(0) != 1)
    {
        std::cout << packet->getString(1) << std::endl;
        return;
    }
    this->_model->setStatusText(packet->getString(1));
}

void    Network::refreshStatus(Packet *packet)
{
    if (packet->getChar(0) != 1)
    {
        std::cout << packet->getString(1) << std::endl;
        return;
    }
    this->_model->setStatus((eStatus)packet->getChar(1));
}

void    Network::refreshList(Packet *packet)
{
    std::vector<Contact *>  list;

    if (packet->getChar(0) != 1)
    {
        std::cout << packet->getString(1) << std::endl;
        return;
    }
    std::string     format;
    unsigned short  size = packet->getList(1, format);

    for (unsigned int i = 0; i < size * format.size(); i += format.size())
        list.push_back(new Contact(this, packet->getString(i + 2), i, packet->getString(i + 3), (eStatus)packet->getChar(i + 4), this->_model->getWin()));
    _model->setContacts(list);
}

void    Network::refreshAdd(Packet *packet)
{
    if (packet->getChar(0) != 1)
    {
        std::cout << packet->getString(1) << std::endl;
        return;
    }
    this->sendList();
}

void    Network::refreshRm(Packet *packet)
{
    if (packet->getChar(0) != 1)
    {
        std::cout << packet->getString(1) << std::endl;
        return;
    }
}

void    Network::refreshBlock(Packet *packet)
{
    if (packet->getChar(0) != 1)
    {
        std::cout << packet->getString(1) << std::endl;
        return;
    }
}

void    Network::handleCall(Packet *packet)
{
    std::string ip;
    std::string login;

    if (packet->getChar(0) != 1)
    {
        std::cout << packet->getString(1) << std::endl;
        return;
    }
    login = packet->getString(1);
    ip = packet->getString(2);
    this->_model->handleCall(login, ip);
}

void    Network::acceptCall(Packet *packet)
{
    std::string ip;
    std::string login;

    if (packet->getChar(0) != 1)
    {
        std::cout << packet->getString(1) << std::endl;
        return;
    }
    login = packet->getString(1);
    ip = packet->getString(2);

    this->_sockUDP->close();
    this->_sockUDP->init(1337, ip.c_str());
    this->_currentClient = true;
    this->_model->openChat(login);
    this->_model->setPlayback(false);
}

void    Network::rejectCall(Packet *packet)
{
    std::string ip;
    std::string login;

    if (packet->getChar(0) != 1)
    {
        std::cout << packet->getString(1) << std::endl;
        return;
    }
    login = packet->getString(1);
    ip = packet->getString(2);
}

void    Network::closeCall(Packet *packet)
{
    if (packet->getChar(0) != 1)
    {
        std::cout << packet->getString(1) << std::endl;
        return;
    }
    this->_model->closeCall();
    if (this->_currentServ)
        this->_sockUDPServ->closeClients();
}

void    Network::receiveChat(Packet *packet)
{
    if (packet->getChar(0) != 1)
    {
        std::cout << packet->getString(1) << std::endl;
        return;
    }
    this->_model->displayMsg(packet->getString(1), packet->getString(2));
}

int     Network::getUID()
{
    return _reqUID++;
}

bool    Network::getInit() const
{
    return this->_init;
}

bool    Network::getHandshake() const
{
    return (this->_handshake);
}

bool    Network::getLog() const
{
    return (this->_log);
}

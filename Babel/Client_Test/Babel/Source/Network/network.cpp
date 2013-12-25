#include "Include/Network/network.h"
#include "Include/Network/Util.hpp"

Network::Network(MyContactModel *model)
    :   _model(model)
{
    _sockUDP = NULL;
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
            handleNetworkTCP();
            handlePackets();
        }
        catch (Exception &e)
        {
            throw Exception(e);
        }
    }
}

void	Network::pushUDP(Packet *packet)
{
    this->_sendQueueUDP.push(packet);
}

void	Network::pushTCP(Packet *packet)
{
    this->_sendQueueTCP.push(packet);
}

void	Network::handleNetworkUDP()
{
    if (_sendQueueUDP.empty() == false && _sockUDP->isWritable())
    {
        Packet	*packet = this->_sendQueueUDP.front();
        this->_sendQueueUDP.pop();
        try
        {
            _sockUDP->send(packet->serialize(), packet->size());
        }
        catch (Exception &e)
        {
            delete _sockUDP;
            _sockUDP = NULL;
            _init = false;
            throw Exception(e);
        }
        delete packet;
    }
    if (_sockUDP->isReadable())
    {
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
        _factory.feed(buffer, rdSize);
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
        for (unsigned int i = 0; i < rdSize; ++i)
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

void    Network::sendStatus(Contact::eStatus status)
{
    Packet  *pack = new Packet(this->getUID(), Packet::STATUS);

    pack->setFormat("c");
    pack->updateData(3);
    pack->appendToData(0, status);
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

void    Network::sendList()
{
    this->_sendQueueTCP.push(new Packet(this->getUID(), Packet::LIST));
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
    this->_model->setStatus((Contact::eStatus)packet->getChar(1));
}

void    Network::refreshList(Packet *packet)
{
    if (packet->getChar(0) != 1)
    {
        std::cout << packet->getString(1) << std::endl;
        return;
    }
    std::string     format;
    unsigned short  size = packet->getList(1, format);

    this->_model->clearContact();
    for (unsigned int i = 0; i < size * format.size(); i += format.size())
        this->_model->addContact(packet->getString(i + 2), packet->getString(i + 3), (Contact::eStatus)packet->getChar(i + 4));
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

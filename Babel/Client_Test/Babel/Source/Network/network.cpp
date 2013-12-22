#include "Include/Network/network.h"
#include "Include/Network/Util.hpp"

Network::Network()
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
        if (packet->getInstruction() == Packet::HANDSHAKE)
            this->sendHandshake();
        else if (packet->getInstruction() == Packet::LOGIN || packet->getInstruction() == Packet::CREATE_ACCOUNT)
            this->checkLogin(packet);
        else
        {
            std::cout << "PACKET NON GERE" << std::endl;
            packet->show();
        }
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
        std::cout << "Data packet factory" << std::endl;
        for (unsigned int i = 0; i < rdSize; ++i)
        {
            std::cout << Util::format('0', 2, Util::toHex<unsigned int>(buffer[i])) << " ";
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

void    Network::checkLogin(Packet *packet)
{
    if (packet->getChar(0) != 1)
    {
        std::cout << packet->getString(1) << std::endl;
        return;
    }
    this->_log = true;
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

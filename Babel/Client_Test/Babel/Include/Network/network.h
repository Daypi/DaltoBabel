#ifndef NETWORK_H
#define NETWORK_H

#include	<iostream>
#include	<queue>
#include	"SocketClientTCP.h"
#include	"SocketClientUDP.h"
#include	"PacketFactory.h"
#include    "Include/Model/contact.h"


class		Network
{
private:
    std::queue<Packet *>	_sendQueueUDP;
    std::queue<Packet *>	_sendQueueTCP;
    SocketClientUDP         *_sockUDP;
    SocketClientTCP         *_sockTCP;
    PacketFactory           _factory;
    bool                    _init;
    bool                    _handshake;
    bool                    _log;
    int                     _reqUID;
    Contact::eStatus        _status;
    std::string             _statusText;

private:
    Network		&operator=(const Network &);

public:
    Network();
    Network(const Network &);
    ~Network();

    void	connect(const std::string &ip, int port);
    void	setInit(bool b);
    void	handleNetwork();
    void	pushUDP(Packet *packet);
    void	pushTCP(Packet *packet);
    void	handleNetworkUDP();
    void	handleNetworkTCP();
    void	handlePackets();

    void    sendHandshake();
    void    sendLogin(bool isNewUser, const std::string &login, const std::string &mdp);
    void    checkLogin(Packet *packet);
    void    refreshStatusText(Packet *packet);
    void    refreshStatus(Packet *packet);
    void    refreshList(Packet  *packet);

    int                 getUID();
    bool                getInit() const;
    bool                getHandshake() const;
    bool                getLog() const;
    const std::string&  getStatusText() const;
    Contact::eStatus             getStatus() const;
};

#endif // NETWORK_H

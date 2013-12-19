#ifndef NETWORK_H
#define NETWORK_H

#include	<iostream>
#include	<queue>
#include	"SocketClientTCP.h"
#include	"SocketClientUDP.h"
#include	"PacketFactory.h"


class		Network
{
    std::queue<Packet *>	_sendQueueUDP;
    std::queue<Packet *>	_sendQueueTCP;
    SocketClientUDP         *_sockUDP;
    SocketClientTCP         *_sockTCP;
    PacketFactory           _factory;
    bool                    _init;
    int                     _reqUID;

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
    int     getUID();
    void	handleNetworkUDP();
    void	handleNetworkTCP();
    void	handlePackets();

    //    void	getLogin(Packet *packet);
    //    void	getRooms(Packet *packet);
    //    void	getMsgChat(Packet *packet);
    //    void	getLevels(Packet *packet);
    //    void	joinRoom(Packet *packet);
    //    void	start(Packet *packet);
    //    void	end(Packet *packet);
    //    void	chatRoom(Packet *packet);
    //    void	listLogins(Packet *packet);
};

#endif // NETWORK_H

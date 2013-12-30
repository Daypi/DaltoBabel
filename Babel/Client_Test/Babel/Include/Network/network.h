#ifndef NETWORK_H
#define NETWORK_H

#include	<iostream>
#include	<queue>
#include	"SocketClientTCP.h"
#include	"SocketClientUDP.h"
#include    "SocketServerUDP.h"
#include	"PacketFactory.h"
#include    "Include/Model/myContactModel.h"

class		Network
{
private:
    std::queue<Packet *>	_sendQueueUDP;
    std::queue<Packet *>	_sendQueueUDPServ;
    std::queue<Packet *>	_sendQueueTCP;
    SocketClientUDP         *_sockUDP;
    SocketServerUDP         *_sockUDPServ;
    SocketClientTCP         *_sockTCP;
    PacketFactory           _factory;
    bool                    _init;
    bool                    _handshake;
    bool                    _log;
    int                     _reqUID;
    MyContactModel          *_model;

private:
    Network		&operator=(const Network &);

public:
    Network(MyContactModel *model);
    Network(const Network &);
    ~Network();

    void	connect(const std::string &ip, int port);
    void	setInit(bool b);
    void	handleNetwork();
    void	pushUDP(Packet *packet);
    void	pushTCP(Packet *packet);
    void	handleNetworkUDP();
    void	handleNetworkUDPServ();
    void	handleNetworkTCP();
    void	handlePackets();

    void    sendHandshake();
    void    sendLogin(bool isNewUser, const std::string &login, const std::string &mdp);
    void    sendStatusText(const std::string &newStat);
    void    sendStatus(eStatus status);
    void    sendList();
    void    addContact(const std::string& name);
    void    rmContact(const std::string& name);
    void    blockContact(const std::string& name);
    void    sendAccept(const std::string& login);
    void    sendReject(const std::string& login);
    void    sendCall(const std::string& login);
    void    sendHangUp();
    void    sendPing();
    void    checkLogin(Packet *packet);
    void    refreshStatusText(Packet *packet);
    void    refreshStatus(Packet *packet);
    void    refreshList(Packet  *packet);
    void    refreshAdd(Packet *packet);
    void    refreshRm(Packet *packet);
    void    refreshBlock(Packet *packet);
    void    handleCall(Packet *packet);
    void    acceptCall(Packet *packet);
    void    rejectCall(Packet *packet);
    void    closeCall(Packet *packet);
    int                 getUID();
    bool                getInit() const;
    bool                getHandshake() const;
    bool                getLog() const;
};

#endif // NETWORK_H

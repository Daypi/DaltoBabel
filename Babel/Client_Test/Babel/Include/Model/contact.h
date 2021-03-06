#ifndef CONTACT_H
#define CONTACT_H

#include <string>
#include <vector>
#include "Include/Model/myChatModel.h"

class Contact
{
private:
    unsigned int    _uid;
    std::string     _ip;
    std::string     _name;
    std::string     _statusText;
    eStatus         _status;
    std::vector<std::string>    _chat;
    MyChatModel     *_c;

public:
    Contact(Network *net, const std::string& name, unsigned int uid, const std::string& statusText, eStatus status, QWidget *parent);
    Contact(const Contact& oldContact);
    ~Contact();

    Contact                 &operator=(const Contact& contact);
    Contact                 *operator=(Contact* contact);
    bool                    operator==(const std::string& name);
    bool                    operator==(const Contact& contact);
    void                    clearChat();
    void                    setMsg(const std::string& msg);
    void                    setChat(const std::vector<std::string>& msg);
    void                    setStatusText(const std::string& status);
    void                    setStatus(eStatus status);
    void                    setName(const std::string& name);
    void                    setIp(const std::string& ip);
    const std::string&      getStatusText() const;
    eStatus                 getStatus() const;
    const std::string&      getName() const;
    const std::string&      getIp() const;
    unsigned int            getId() const;
    std::vector<std::string>&    getChat();

    void                    myShow();
    void                    setCalling(bool b);
    bool                    isCalling() const;
    void                    close();
    void                    displayMsg(const std::string &login, const std::string &msg);
};

#endif // CONTACT_H

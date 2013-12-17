#ifndef MYCHATW_H
#define MYCHATW_H

#include "Include/Window/chatWindow.h"

class MyChatModel
{
  ChatWindow  *_w;
  bool        _call;

public:
  MyChatModel(const std::string &name, QWidget *parent);
  ~MyChatModel();

  void        myShow();
  void        setChat(std::vector<std::string> &hist);
  void        setCalling(bool b);
  bool        isCalling() const;
};

#endif // MYCHATW_H

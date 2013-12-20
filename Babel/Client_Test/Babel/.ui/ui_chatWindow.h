/********************************************************************************
** Form generated from reading UI file 'chatWindow.ui'
**
** Created: Fri Dec 20 21:54:17 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWINDOW_H
#define UI_CHATWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_ChatWindow
{
public:
    QGridLayout *gridLayout;
    QPushButton *send;
    QTextEdit *chat;
    QHBoxLayout *horizontalLayout;
    QPushButton *call;
    QPushButton *close;
    QLabel *name;
    QLineEdit *msg;
    QPushButton *wizz;

    void setupUi(QDialog *ChatWindow)
    {
        if (ChatWindow->objectName().isEmpty())
            ChatWindow->setObjectName(QString::fromUtf8("ChatWindow"));
        ChatWindow->resize(640, 480);
        gridLayout = new QGridLayout(ChatWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        send = new QPushButton(ChatWindow);
        send->setObjectName(QString::fromUtf8("send"));

        gridLayout->addWidget(send, 2, 2, 1, 1);

        chat = new QTextEdit(ChatWindow);
        chat->setObjectName(QString::fromUtf8("chat"));
        chat->setEnabled(true);
        chat->setReadOnly(true);

        gridLayout->addWidget(chat, 1, 1, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        call = new QPushButton(ChatWindow);
        call->setObjectName(QString::fromUtf8("call"));

        horizontalLayout->addWidget(call);

        close = new QPushButton(ChatWindow);
        close->setObjectName(QString::fromUtf8("close"));

        horizontalLayout->addWidget(close);


        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 2);

        name = new QLabel(ChatWindow);
        name->setObjectName(QString::fromUtf8("name"));

        gridLayout->addWidget(name, 0, 0, 1, 1);

        msg = new QLineEdit(ChatWindow);
        msg->setObjectName(QString::fromUtf8("msg"));

        gridLayout->addWidget(msg, 2, 1, 1, 1);

        wizz = new QPushButton(ChatWindow);
        wizz->setObjectName(QString::fromUtf8("wizz"));

        gridLayout->addWidget(wizz, 2, 0, 1, 1);


        retranslateUi(ChatWindow);
        QObject::connect(close, SIGNAL(clicked()), ChatWindow, SLOT(hide()));

        QMetaObject::connectSlotsByName(ChatWindow);
    } // setupUi

    void retranslateUi(QDialog *ChatWindow)
    {
        ChatWindow->setWindowTitle(QApplication::translate("ChatWindow", "Dialog", 0, QApplication::UnicodeUTF8));
        send->setText(QApplication::translate("ChatWindow", "Send", 0, QApplication::UnicodeUTF8));
        chat->setHtml(QApplication::translate("ChatWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0, QApplication::UnicodeUTF8));
        call->setText(QApplication::translate("ChatWindow", "Call", 0, QApplication::UnicodeUTF8));
        close->setText(QApplication::translate("ChatWindow", "Close", 0, QApplication::UnicodeUTF8));
        name->setText(QApplication::translate("ChatWindow", "Name", 0, QApplication::UnicodeUTF8));
        wizz->setText(QApplication::translate("ChatWindow", "WIZZ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ChatWindow: public Ui_ChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H

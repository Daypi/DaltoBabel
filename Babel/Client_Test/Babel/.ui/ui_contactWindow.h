/********************************************************************************
** Form generated from reading UI file 'contactWindow.ui'
**
** Created: Sat Dec 21 16:01:34 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTACTWINDOW_H
#define UI_CONTACTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ContactWindow
{
public:
    QGridLayout *gridLayout;
    QListWidget *listContact;
    QPushButton *chat;
    QPushButton *block;
    QPushButton *remove;
    QPushButton *add;
    QPushButton *call;
    QPushButton *wizz;
    QFrame *line;

    void setupUi(QDialog *ContactWindow)
    {
        if (ContactWindow->objectName().isEmpty())
            ContactWindow->setObjectName(QString::fromUtf8("ContactWindow"));
        ContactWindow->resize(367, 720);
        gridLayout = new QGridLayout(ContactWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        listContact = new QListWidget(ContactWindow);
        listContact->setObjectName(QString::fromUtf8("listContact"));

        gridLayout->addWidget(listContact, 0, 0, 1, 3);

        chat = new QPushButton(ContactWindow);
        chat->setObjectName(QString::fromUtf8("chat"));

        gridLayout->addWidget(chat, 4, 1, 1, 1);

        block = new QPushButton(ContactWindow);
        block->setObjectName(QString::fromUtf8("block"));

        gridLayout->addWidget(block, 1, 2, 1, 1);

        remove = new QPushButton(ContactWindow);
        remove->setObjectName(QString::fromUtf8("remove"));

        gridLayout->addWidget(remove, 1, 1, 1, 1);

        add = new QPushButton(ContactWindow);
        add->setObjectName(QString::fromUtf8("add"));

        gridLayout->addWidget(add, 1, 0, 1, 1);

        call = new QPushButton(ContactWindow);
        call->setObjectName(QString::fromUtf8("call"));

        gridLayout->addWidget(call, 4, 0, 1, 1);

        wizz = new QPushButton(ContactWindow);
        wizz->setObjectName(QString::fromUtf8("wizz"));

        gridLayout->addWidget(wizz, 4, 2, 1, 1);

        line = new QFrame(ContactWindow);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 2, 0, 1, 3);

        QWidget::setTabOrder(call, chat);
        QWidget::setTabOrder(chat, wizz);
        QWidget::setTabOrder(wizz, add);
        QWidget::setTabOrder(add, remove);
        QWidget::setTabOrder(remove, block);
        QWidget::setTabOrder(block, listContact);

        retranslateUi(ContactWindow);

        QMetaObject::connectSlotsByName(ContactWindow);
    } // setupUi

    void retranslateUi(QDialog *ContactWindow)
    {
        ContactWindow->setWindowTitle(QApplication::translate("ContactWindow", "DaltoBabel", 0, QApplication::UnicodeUTF8));
        chat->setText(QApplication::translate("ContactWindow", "CHAT", 0, QApplication::UnicodeUTF8));
        block->setText(QApplication::translate("ContactWindow", "Block contact", 0, QApplication::UnicodeUTF8));
        remove->setText(QApplication::translate("ContactWindow", "Remove contact", 0, QApplication::UnicodeUTF8));
        add->setText(QApplication::translate("ContactWindow", "Add contact", 0, QApplication::UnicodeUTF8));
        call->setText(QApplication::translate("ContactWindow", "CALL", 0, QApplication::UnicodeUTF8));
        wizz->setText(QApplication::translate("ContactWindow", "WIZZ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ContactWindow: public Ui_ContactWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTACTWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'connectWindow.ui'
**
** Created: Sat Dec 21 16:01:34 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTWINDOW_H
#define UI_CONNECTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_ConnectWindow
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QLabel *login;
    QHBoxLayout *horizontalLayout;
    QCheckBox *newUser;
    QSpacerItem *horizontalSpacer;
    QPushButton *valider;
    QSpacerItem *verticalSpacer;
    QLabel *mdp;
    QLineEdit *editLogin;
    QLineEdit *editMdp;
    QSpacerItem *verticalSpacer_2;
    QLineEdit *editIP;
    QLabel *IP;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *ConnectWindow)
    {
        if (ConnectWindow->objectName().isEmpty())
            ConnectWindow->setObjectName(QString::fromUtf8("ConnectWindow"));
        ConnectWindow->resize(854, 480);
        ConnectWindow->setMinimumSize(QSize(854, 480));
        ConnectWindow->setMaximumSize(QSize(854, 480));
        gridLayout = new QGridLayout(ConnectWindow);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        login = new QLabel(ConnectWindow);
        login->setObjectName(QString::fromUtf8("login"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        font.setStrikeOut(false);
        login->setFont(font);
        login->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(login, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        newUser = new QCheckBox(ConnectWindow);
        newUser->setObjectName(QString::fromUtf8("newUser"));

        horizontalLayout->addWidget(newUser);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        valider = new QPushButton(ConnectWindow);
        valider->setObjectName(QString::fromUtf8("valider"));

        horizontalLayout->addWidget(valider);


        gridLayout_2->addLayout(horizontalLayout, 3, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 1, 1, 1);

        mdp = new QLabel(ConnectWindow);
        mdp->setObjectName(QString::fromUtf8("mdp"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        mdp->setFont(font1);
        mdp->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(mdp, 2, 0, 1, 1);

        editLogin = new QLineEdit(ConnectWindow);
        editLogin->setObjectName(QString::fromUtf8("editLogin"));
        editLogin->setMaxLength(32);

        gridLayout_2->addWidget(editLogin, 1, 1, 1, 1);

        editMdp = new QLineEdit(ConnectWindow);
        editMdp->setObjectName(QString::fromUtf8("editMdp"));
        editMdp->setMaxLength(32);
        editMdp->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(editMdp, 2, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 4, 1, 1, 1);

        editIP = new QLineEdit(ConnectWindow);
        editIP->setObjectName(QString::fromUtf8("editIP"));

        gridLayout_2->addWidget(editIP, 5, 1, 1, 1);

        IP = new QLabel(ConnectWindow);
        IP->setObjectName(QString::fromUtf8("IP"));
        IP->setFont(font1);
        IP->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(IP, 5, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        QWidget::setTabOrder(editLogin, editMdp);
        QWidget::setTabOrder(editMdp, editIP);
        QWidget::setTabOrder(editIP, valider);
        QWidget::setTabOrder(valider, newUser);

        retranslateUi(ConnectWindow);

        QMetaObject::connectSlotsByName(ConnectWindow);
    } // setupUi

    void retranslateUi(QDialog *ConnectWindow)
    {
        ConnectWindow->setWindowTitle(QApplication::translate("ConnectWindow", "DaltoConnect", 0, QApplication::UnicodeUTF8));
        login->setText(QApplication::translate("ConnectWindow", "Pseudo", 0, QApplication::UnicodeUTF8));
        newUser->setText(QApplication::translate("ConnectWindow", "New User ?", 0, QApplication::UnicodeUTF8));
        valider->setText(QApplication::translate("ConnectWindow", "valider", 0, QApplication::UnicodeUTF8));
        mdp->setText(QApplication::translate("ConnectWindow", "Mot de passe", 0, QApplication::UnicodeUTF8));
        IP->setText(QApplication::translate("ConnectWindow", "IP", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConnectWindow: public Ui_ConnectWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTWINDOW_H

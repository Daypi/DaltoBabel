TARGET = Babel

HEADERS += \
    Include/Window/contactWindow.h \
    Include/Window/connectWindow.h \
    Include/Window/chatWindow.h \
    Include/Model/contact.h \
    Include/Model/myContactModel.h \
    Include/Model/myChatModel.h \
    Include/Model/myConnectModel.h

SOURCES += \
    Source/main.cpp \
    Source/Window/contactWindow.cpp \
    Source/Window/connectWindow.cpp \
    Source/Window/chatWindow.cpp \
    Source/Model/contact.cpp \
    Source/Model/myContactModel.cpp \
    Source/Model/myChatModel.cpp \
    Source/Model/myConnectModel.cpp

FORMS += \
    Source/Window/contactWindow.ui \
    Source/Window/connectWindow.ui \
    Source/Window/chatWindow.ui

release: DESTDIR = .
debug:   DESTDIR = .

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui

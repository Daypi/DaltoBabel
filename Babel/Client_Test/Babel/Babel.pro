TARGET = Babel

HEADERS += \
    Include/Window/contactWindow.h \
    Include/Window/connectWindow.h \
    Include/Window/chatWindow.h \
    Include/Model/contact.h \
    Include/Model/myContactModel.h \
    Include/Model/myChatModel.h \
    Include/Model/myConnectModel.h \
    Include/Network/network.h \
    Include/Network/Thread.hpp \
    Include/Network/SocketServerUDP.h \
    Include/Network/SocketServerTCP.h \
    Include/Network/SocketClientUDP.h \
    Include/Network/SocketClientTCP.h \
    Include/Network/SocketAvd.hh \
    Include/Network/Socket.hh \
    Include/Network/SeleKtor.hh \
    Include/Network/PacketFactory.h \
    Include/Network/Packet.h \
    Include/Network/MutexPool.h \
    Include/Network/Mutex.h \
    Include/Network/IThread.h \
    Include/Network/ISocketServer.h \
    Include/Network/ISocketClient.h \
    Include/Network/ISocket.hh \
    Include/Network/IMutex.h \
    Include/Network/ICondVar.h \
    Include/Network/Exception.h \
    Include/Network/CUThread.hpp \
    Include/Network/CUSocket.hh \
    Include/Network/CUMutex.h \
    Include/Network/CUCondVar.h \
    Include/Network/CondVar.hh \
    Include/Network/CircularBuffer.hpp \
    Include/Network/Util.hpp

SOURCES += \
    Source/main.cpp \
    Source/Window/contactWindow.cpp \
    Source/Window/connectWindow.cpp \
    Source/Window/chatWindow.cpp \
    Source/Model/contact.cpp \
    Source/Model/myContactModel.cpp \
    Source/Model/myChatModel.cpp \
    Source/Model/myConnectModel.cpp \
    Source/Network/network.cpp \
    Source/Network/socketServerUDP.cpp \
    Source/Network/SocketServerTCP.cpp \
    Source/Network/SocketClientUDP.cpp \
    Source/Network/SocketClientTCP.cpp \
    Source/Network/SocketAvd.cpp \
    Source/Network/Socket.cpp \
    Source/Network/SeleKtor.cpp \
    Source/Network/PacketFactory.cpp \
    Source/Network/Packet.cpp \
    Source/Network/MutexPool.cpp \
    Source/Network/Mutex.cpp \
    Source/Network/Exception.cpp \
    Source/Network/CUSocket.cpp \
    Source/Network/CUMutex.cpp \
    Source/Network/CUCondVar.cpp \
    Source/Network/CondVar.cpp \
    Source/Network/CircularBuffer.cpp

FORMS += \
    Source/Window/contactWindow.ui \
    Source/Window/chatWindow.ui \
    Source/Window/connectWindow.ui

release: DESTDIR = .
debug:   DESTDIR = .

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui

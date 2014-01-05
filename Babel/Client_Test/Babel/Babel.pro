TARGET = Babel

QT += widgets

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
    Include/Network/CondVar.hh \
    Include/Network/CircularBuffer.hpp \
    Include/Network/Util.hpp \
    Include/Network/LibC.h \
    Include/Network/TimeStamp.h \
    Include/Network/AudioManager.hh \
    Include/Network/babel_common.h \
    Include/Network/IAudioIO.hh \
    Include/Network/ICompressor.hh \
    Include/Network/OpusCompressor.hh \
    Include/Network/portaudio.h \
    Include/Network/PortAudioIO.hh \
    Include/Network/opus.h \
    Include/Network/opus_custom.h \
    Include/Network/opus_defines.h \
    Include/Network/opus_multistream.h \
    Include/Network/opus_types.h \
    Include/Network/dsconf.h \
    Include/Network/dsound.h \
    Include/Network/pa_asio.h \
    Include/Network/pa_jack.h \
    Include/Network/pa_linux_alsa.h \
    Include/Network/pa_mac_core.h \
    Include/Network/pa_win_ds.h \
    Include/Network/pa_win_wasapi.h \
    Include/Network/pa_win_waveformat.h \
    Include/Network/pa_win_wmme.h

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
    Source/Network/CondVar.cpp \
    Source/Network/CircularBuffer.cpp \
    Source/Network/LibC.cpp \
    Source/Network/TimeStamp.cpp \
    Source/Network/AudioManager.cpp \
    Source/Network/OpusCompressor.cpp \
    Source/Network/PortAudioIO.cpp

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

INCLUDEPATH += .

win32 {
SOURCES += \
    Source/Network/CWSocket.cpp \
    Source/Network/CWMutex.cpp \
    Source/Network/CWCondVar.cpp

HEADERS += \
    Include/Network/CWThread.hpp \
    Include/Network/CWSocket.hh \
    Include/Network/CWMutex.h \
    Include/Network/CWCondVar.h
}

!win32 {
SOURCES += \
    Source/Network/CUSocket.cpp \
    Source/Network/CUMutex.cpp \
    Source/Network/CUCondVar.cpp

HEADERS += \
    Include/Network/CUThread.hpp \
    Include/Network/CUSocket.hh \
    Include/Network/CUMutex.h \
    Include/Network/CUCondVar.h

}

unix:!macx: LIBS += -L$$PWD/ -lportaudio

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

unix:!macx: PRE_TARGETDEPS += $$PWD/libportaudio.a


unix:!macx: LIBS += -lrt


unix:!macx: LIBS += -lasound

unix:!macx: LIBS += -ljack

unix:!macx: LIBS += -lopus

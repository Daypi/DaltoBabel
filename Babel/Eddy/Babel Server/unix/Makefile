##
## Makefile for Server in /home/taiebi_e//tek3/Babel/DaltoBabel/Babel/Eddy/Babel Server/unix
##
## Made by eddy taiebi
## Login   <taiebi_e@epitech.net>
##
## Started on  Sun Dec 22 13:29:59 2013 eddy taiebi
## Last update Mon Dec 30 19:04:10 2013 eddy taiebi
##

NAME=	server

SRC=	../shared/src/LibC.cpp \
	../shared/src/Account.cpp \
	../shared/src/AccountManager.cpp \
	../shared/src/CircularBuffer.cpp \
	../shared/src/CondVar.cpp \
	../shared/src/CUCondVar.cpp \
	../shared/src/CUFolder.cpp \
	../shared/src/CUMutex.cpp \
	../shared/src/CUSocket.cpp \
	../shared/src/Exception.cpp \
	../shared/src/Folder.cpp \
	../shared/src/main.cpp \
	../shared/src/Mutex.cpp \
	../shared/src/MutexPool.cpp \
	../shared/src/Packet.cpp \
	../shared/src/PacketFactory.cpp \
	../shared/src/SeleKtor.cpp \
	../shared/src/Server.cpp \
	../shared/src/Socket.cpp \
	../shared/src/SocketAvd.cpp \
	../shared/src/SocketServerTCP.cpp \
	../shared/src/TimeStamp.cpp \
	../shared/src/User.cpp \
	../shared/src/UserCollection.cpp

OBJ=	$(SRC:.cpp=.o)

CXX=	g++ -W -Wall -Wextra -I../shared/include/ -g3

$(NAME):	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) -lpthread

all:	$(NAME)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean $(NAME)

.PHONY:	all clean fclean re

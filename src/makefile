NAME		= 	Inotified

SRC 		=   main.cpp \
        		common/Logger.cpp \
        		platform/linux/InotifyWrapper.cpp

OBJS 		=	${SRC:.cpp=.o}

CXXFLAGS	= 	-g -ansi -W -Wall -pedantic -std=c++11 -fpic

LIBS		= 	-lcrypto

CXX			= 	g++


all			: 	$(OBJS)
				$(CXX) -o $(NAME) $(OBJS) $(CXXFLAGS) $(LIBS)

clean		:
				rm -f $(OBJS)

re			:	all clean
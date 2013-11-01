##
## Makefile
##

CXX	= g++

RM	= rm -f

NAME	= rtype-server

SRCS	= Main.cpp Server.cpp config/ConfigMgr.cpp utils/Utils.cpp utils/Thread.cpp utils/Socket.cpp \
		  game/Game.cpp

OBJS	= $(SRCS:.cpp=.o)

ifeq ($(OS),Windows_NT)
	CXXFLAGS += -D WIN32
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		CXXFLAGS += -D AMD64
	endif

	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		CXXFLAGS += -D IA32
	endif
	LDFLAGS += -lWs2_32
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CXXFLAGS += -D LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		CXXFLAGS += -D OSX -stdlib=libc++
		LDFLAGS += -stdlib=libc++
	endif
endif

#CXXFLAGS	+= -Wall
CXXFLAGS	+= -std=c++0x
CXXFLAGS	+= -I. -Iconfig -Iutils -Igame

LDFLAGS	+= -lpthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re


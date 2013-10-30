##
## Makefile
## 

CXX	= g++

RM	= rm -f

CXXFLAGS	+= -Wall -Werror
CXXFLAGS	+= -std=c++11
CXXFLAGS	+= -I. -Iconfig -Iutils

LDFLAGS	= -lpthread

NAME	= rtype-server

SRCS	= Main.cpp Server.cpp config/ConfigMgr.cpp utils/Utils.cpp utils/Runnable.cpp

OBJS	= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re


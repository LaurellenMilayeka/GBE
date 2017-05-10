DEBUG ?= false

SRCDIR=		./src/
INCDIR=		./include/

SRC=		$(SRCDIR)cpu/Z80.cpp \
		$(SRCDIR)cpu/Opcodes.cpp \
		$(SRCDIR)cpu/Disasm.cpp \
\
		$(SRCDIR)loader/ROMLoader.cpp \
\
		$(SRCDIR)bios/BIOS.cpp \
\
		$(SRCDIR)ram/RAM.cpp \
\
		$(SRCDIR)debug/Hexdump.cpp \
\
		$(SRCDIR)main.cpp

OBJS=		$(SRC:.cpp=.o)

CXXFLAGS=	-Wall -Wextra -Werror -std=c++11 -g3
CXXFLAGS+=	-I $(INCDIR)cpu/ -I $(INCDIR)loader/ -I $(INCDIR)bios/ -I $(INCDIR)ram/ -I $(INCDIR)

ifeq ($(DEBUG), true)
CXXFLAGS+= -DDEBUG
endif

CXX=		g++

NAME=		GBEmu

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CXX) -o $(NAME) $(OBJS)

clean:
		rm -rf $(OBJS)

fclean:		clean
		rm -rf $(NAME)

re:		fclean all

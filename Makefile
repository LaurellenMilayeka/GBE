DEBUG ?= false

SRCDIR=		./src/
INCDIR=		./include/

SRC=		$(SRCDIR)main.cpp \
\
		$(SRCDIR)cpu/Z80.cpp \
		$(SRCDIR)cpu/Opcodes.cpp \
		$(SRCDIR)cpu/Disasm.cpp \
\
		$(SRCDIR)loader/ROMLoader.cpp \
\
		$(SRCDIR)bios/BIOS.cpp \
		$(SRCDIR)bios/Boot.cpp \
\
		$(SRCDIR)ram/RAM.cpp \
\
		$(SRCDIR)video/GPU.cpp \
\
		$(SRCDIR)window/CoreWindow.cpp \
\
		$(SRCDIR)control/Joypad.cpp \
\
		$(SRCDIR)debug/Hexdump.cpp \
		$(SRCDIR)debug/RegDump.cpp \
		$(SRCDIR)debug/DebugShell.cpp

OBJS=		$(SRC:.cpp=.o)

CXXFLAGS=	-Wall -Wextra -std=c++11 -g3
CXXFLAGS+=	-I $(INCDIR)cpu/ -I $(INCDIR)loader/ -I $(INCDIR)bios/ -I $(INCDIR)ram/ -I $(INCDIR) -I $(INCDIR)video/ -I $(INCDIR)debug/ -I $(INCDIR)window/ -I $(INCDIR)sound/ -I $(INCDIR)control/

ifeq ($(DEBUG), true)
LDFLAGS=	-lGL -lGLEW -lSDL2 -lSDL2main -lpthread
CXXFLAGS+= -DDEBUG
endif

ifeq ($(STS), true)
LDFLAGS=	-lGL -lGLEW -lSDL2 -lSDL2main -lpthread
CXXFLAGS+= -DSTS_DBG
endif

ifeq ($(NO_GRAPHICS), true)
LDFLAGS=
CXXFLAGS+= -DNOGRAPHICS
endif

CXX=		g++

NAME=		GBEmu

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CXX) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
		rm -rf $(OBJS)
		find . -name '*~' -exec rm {} \;

fclean:		clean
		rm -rf $(NAME)

re:		fclean all

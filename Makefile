CXX = g++
CXXFLAGS = -g -Wall -Wno-unknown-pragmas -I./include
OBJDIR = obj
BINDIR = bin
SRCDIR = src
INCLUDE_DIR = include
_INCL = BST.h Node.h ServerModel.h ClientModel.h
INCL = $(patsubst %,$(INCLUDE_DIR)/%,$(_INCL))
_OBJ = Node.o BST.o ServerModel.o client.o server.o ClientModel.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

ifdef OS
    RM = del /Q
    MKDIR = mkdir
    EXE_EXT = .exe
    LIBS = -lws2_32
else
    RM = rm -rf
    MKDIR = mkdir -p
    EXE_EXT =
    LIBS =
endif

all: directories client_bin server_bin

directories: $(OBJDIR) $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

client_bin: $(OBJDIR)/client.o $(OBJDIR)/Node.o $(OBJDIR)/BST.o $(OBJDIR)/ServerModel.o $(OBJDIR)/ClientModel.o
	$(CXX) -o $(BINDIR)/client$(EXE_EXT) $^ $(LIBS)

server_bin: $(OBJDIR)/server.o $(OBJDIR)/Node.o $(OBJDIR)/BST.o $(OBJDIR)/ServerModel.o 
	$(CXX) -o $(BINDIR)/server$(EXE_EXT) $^ $(LIBS)


$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCL)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

clean:
	$(RM) $(OBJDIR) $(BINDIR)

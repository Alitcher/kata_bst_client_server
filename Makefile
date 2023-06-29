CXX = g++
CXXFLAGS = -g -Wall -I./include
OBJDIR = obj
BINDIR = bin
SRCDIR = src
INCLUDE_DIR = include
_INCL = BST.h Node.h ServerModel.h
INCL = $(patsubst %,$(INCLUDE_DIR)/%,$(_INCL))
_OBJ = Node.o BST.o ServerModel.o client.o server.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

all: directories client_bin server_bin

directories: $(OBJDIR) $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

client_bin: $(OBJDIR)/client.o $(OBJDIR)/Node.o $(OBJDIR)/BST.o $(OBJDIR)/ServerModel.o
	$(CXX) -o $(BINDIR)/client $^

server_bin: $(OBJDIR)/server.o $(OBJDIR)/Node.o $(OBJDIR)/BST.o $(OBJDIR)/ServerModel.o
	$(CXX) -o $(BINDIR)/server $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCL)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

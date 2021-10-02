
CC = clang
CXXFLAGS = -std=c11 -Wall -g
LDFLAGS =


APPNAME = myapp.out
SRCDIR = src
OBJDIR = obj

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

RM = rm
DELOBJ = $(OBJ)

all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)


# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CXXFLAGS) -o $@ -c $<


.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(APPNAME)

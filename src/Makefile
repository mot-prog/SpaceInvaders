CC      = gcc
LDFLAGS = -L Graphique-2.0
LDLIBS = -lgraph -lSDL2 -lSDL2_ttf
CFLAGS = -Wall -Wextra -MMD -MP 
SRCS = $(wildcard C_files/*.c)
OBJS = $(addprefix build/, $(SRCS:.c=.o))
TARGET = build/main

all: $(TARGET) | build
	$(TARGET)

$(TARGET): $(OBJS) | build
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@ 

build/%.o: %.c | build
#fabrique le sous dossier "Fonctions" dans le build
	mkdir -p $(dir $@) 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build

build:
	mkdir -p build

-include $(wildcard build/*.d)

.PHONY: clean
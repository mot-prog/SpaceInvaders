CC      = gcc
LDFLAGS = -L ../Graphique-2.0
LDLIBS = -lgraph -lSDL2 -lSDL2_ttf
CFLAGS = -Wall -Wextra 
SRCS = $(wildcard *.c) 
OBJS = $(SRCS:.c=.o)
TARGET = test

all: $(TARGET) 
	./$(TARGET)

$(TARGET): $(OBJS) 
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@ 

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:$(OBJS)
	rm -rf $(OBJS) $(TARGET)

.PHONY: clean
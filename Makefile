OBJS = src/main.o src/thread_pool.o lib/simclist.o
DEPS = $(OBJS:.o=.d)
CC = gcc
CFLAGS = -g3 -Wall -fpic -std=gnu99 -MMD -MP
BIN = ./xmpp
LDLIBS = -pthread

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(LDLIBS) $(OBJS) -o$(BIN)

%.d: %.c

clean:
	-rm -f $(OBJS) $(BIN) src/*.d
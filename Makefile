NAME = night_watchman

CFLAGS = -g -o $(NAME)
CFLAGS += -lcurl -lconfig \
          -fPIE -fstack-protector-strong \
          -Wformat -Wformat-security

LDFLAGS += -pie -Wl,--as-needed,-z,relro,-z,now
CFLAGS += -export-dynamic `pkg-config --cflags --libs gtk+-3.0`

SRCS = main.c
CC = gcc
 
night_watchman: night_watchman.c
 
clean:
		/bin/rm -f $(NAME)

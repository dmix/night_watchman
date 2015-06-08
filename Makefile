NAME = night_watchman

CFLAGS = -g -o $(NAME)
CFLAGS += -lcurl -lconfig \
          -fPIE -fstack-protector-strong \
          -Wformat -Wformat-security
CFLAGS += -export-dynamic `pkg-config --cflags --libs gtk+-3.0`

LDFLAGS += -pie -Wl,--as-needed,-z,relro,-z,now

SRCS = main.c
CC = gcc
 
night_watchman: night_watchman.c

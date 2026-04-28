PWD := $(shell pwd)

CC = gcc
CFLAGS = -Wall -g -O2

SUBDIRS := mysed myfile mywc mytrans

SRCS = src/mybash/main.c \
       src/mysed/mysed.c \
       src/myfile/myfile.c \
       src/mywc/mywc.c \
       src/mytrans/myhash.c \
       src/mytrans/mytrans.c

OBJS := $(SRCS:.c=.o)

BINDIR = bin
OBJDIR = obj

all: $(BINDIR)/mybash

$(BINDIR)/mybash: $(OBJS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -f $(OBJS)
	rm -f $(BINDIR)/mybash

.PHONY: all clean
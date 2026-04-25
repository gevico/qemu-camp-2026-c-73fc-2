CC = gcc
CFLAGS = -Wall -g -O2


TARGET = 19_mytrans
SRCS = 19_mytrans.c mytrans.c myhash.c
OBJS := $(SRCS:.c=.o)

all: $(TARGET)

# TODO: 在这里添加你的代码
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 编译每个 .c 文件为 .o 文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

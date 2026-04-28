CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = 18_mywc
SRCS = 18_mywc.c mywc.c
OBJS := $(SRCS:.c=.o)

all: $(TARGET)

# TODO: 在这里添加你的代码
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 编译每个 .c 文件为 .o 文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean

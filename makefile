# Ethan O'Connor
# ECE 231 Lab 2
# 3/1/25

CC = gcc           # use gcc
CFLAGS = -Wall -O2 # Optimizations and warnings
TARGET = blink_led # Output file

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

clean:
	rm -f $(TARGET) time_diff_file.txt
CC     = gcc
TARGET = clock
SRCS   = clock.c
CFLAGS = -Wall -std=c99
LIBS   = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

$(TARGET): $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)

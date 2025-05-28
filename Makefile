CC = gcc
CFLAGS = -Wall -Wextra -std=c99

TARGET = test

MAIN_SRC = tema.c
FUNC_SRC = functii.c

OBJS = tema.o functii.o


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

tema.o: $(MAIN_SRC) 
	$(CC) $(CFLAGS) -c $(MAIN_SRC) -o tema.o

functii.o: $(FUNC_SRC) 
	$(CC) $(CFLAGS) -c $(FUNC_SRC) -o functii.o

clean:
	rm -f $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET) $(INPUT) $(OUTPUT)

.PHONY: all clean run 
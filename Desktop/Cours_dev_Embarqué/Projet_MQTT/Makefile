# Variables
TARGET = morse_mqtt
RM = rm --interactive=once -vf
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Phony targets
.PHONY: default build clean distclean run

# Default target
default: build

# Build target
build: $(TARGET)

# Linking step
$(TARGET): main.o mqtt.o morse.o led.o
	$(CC) $^ -o $@

# Dependencies for source files
main.o: mqtt.h morse.h led.h
mqtt.o: mqtt.h
morse.o: morse.h
led.o: led.h

# Pattern rule for object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files
clean:
	$(RM) *.o

# Clean up everything
distclean: clean
	$(RM) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)
          
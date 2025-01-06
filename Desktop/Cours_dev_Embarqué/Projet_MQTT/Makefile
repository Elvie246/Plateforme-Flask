# Nom de l'exécutable final
TARGET = morse_mqtt

# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -std=c11 -DFAKE_LED=1

# Bibliothèques nécessaires
LIBS = -lmosquitto

# Liste des fichiers sources
SRCS = main.c mqtt.c morse.c led.c

# Liste des fichiers objets générés
OBJS = $(SRCS:.c=.o)

# Règle par défaut
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

# Règles pour compiler les fichiers objets
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -vf $(OBJS) $(TARGET)

# Exécution du programme
run: $(TARGET)
	./$(TARGET)

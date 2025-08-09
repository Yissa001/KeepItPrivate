#Compilador y flags

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -O2
LDFLAGS = -lssl -lcrypto
TARGET = guiAccess

SRC = guiAccess.c

#Regla principal, se ejecuta al escribir make
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Compilación exitosa. Ejecuta ./$(TARGET)"

#Limpieza de archivos generados
clean: 
	rm -f $(TARGET)
	@echo "Binarios eliminados"

#Instala dependencias (En arch linux)
install-deps:
	sudo pacman -S --needed  openssl
	@echo "Dependencias instaladas"

#Ayuda
help:
	@echo "Opciones disponibles:"
	@echo "	make		Compila el proyecto"
	@echo "	make clean	Elimina binarios"
	@echo "	make install-deps	Instala OpenSSL (En Arch Linux)"
	@echo "make help 	Muestra esta ayuda"

.PHONY: all clean install-deps help


#Compilador y flags

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11
LDFLAGS = -lssl -lcrypto
TARGET = guiAccess

SOURCES = guiAccess.c

#Regla principal, se ejecuta al escribir make
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	@echo "Compilación exitosa. Ejecuta ./$(TARGET)"

#Limpieza de archivos generados
clean: 
	rm -f $(TARGET)
	@echo "Binarios eliminados"

#Instala dependencias (En arch linux)
install-deps:
	sudo pacman -S openssl
	@echo"Dependencias instaladas"

#Ayuda
help:
	@echo "Opciones disponibles:"
	@echo "	make		Compila el proyecto"
	@echo "	make clean	Elimina binarios"
	@echo "	make install-deps	Instala OpenSSL (En Arch Linux)"
	@echo "make help 	Muestra esta ayuda"

.PHONY: all clean install-deps help


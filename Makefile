CC = gcc
CFLAGS = -Wall

CFLAGS += $(shell pkg-config --cflags gtk+-3.0)
LIBS += $(shell pkg-config --libs gtk+-3.0) -lsqlite3

SRCS = interfaz.c funciones_ig.c algoritmo_recomendacion.c
OBJS = $(SRCS:.c=.o)
TARGETS = interfaz algoritmo_recomendacion

all: $(TARGETS)

interfaz: interfaz.o funciones_ig.o
	$(CC) $(CFLAGS) interfaz.o funciones_ig.o -o interfaz $(LIBS)

algoritmo_recomendacion: algoritmo_recomendacion.o
	$(CC) $(CFLAGS) algoritmo_recomendacion.o -o algoritmo_recomendacion $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGETS) $(OBJS)


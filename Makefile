OBJ = main.o field.o ship.o engine.o graphics.o GUI.o
CFLAGS = -Wall -lpthread -lm `pkg-config --cflags --libs cairo gtk+-3.0`

all: bin

bin: $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o bin

%.o : %.c
	gcc $(CFLAGS) -c $<

clean:
	rm bin $(OBJ)

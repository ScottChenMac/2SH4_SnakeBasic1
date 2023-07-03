CC=gcc
CFLAGS=-I.
OBJ = MacUILib.o GameObjects.o Snake.o SnakeGame.o 
DEPS = *.h
#POSTLINKER = -lncurses   ## uncomment this if on Linux
EXEC = ../build/DecomProg

%.o: %.c $(DEPENDS)
	$(CC) -c -o $@ $< $(CFLAGS)

${EXEC} : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) ${POSTLINKER}

clean :
	rm -rf ${OBJ} ${EXEC}


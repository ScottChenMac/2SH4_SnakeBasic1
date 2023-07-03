CC=gcc
CFLAGS=-I.
OBJ = MacUILib.o GameObjects.o Snake.o SnakeGame.o 
DEPS = ${OBJ:.o=.d}
#POSTLINKER = -lncurses   ## uncomment this if on Linux
EXEC = ../build/DecomProg

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

${EXEC} : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) ${POSTLINKER}

-include ${DEPS}

clean :
	rm -rf ${DEPS} ${OBJ} ${EXEC}


CXX = gcc
CXXFLAGS = -g -Wall -MMD
OBJECTS = MacUILib.o GameObjects.o Snake.o SnakeGame.o 
DEPENDS = ${OBJECTS:.o=.d}
EXEC = ../build/DecomProg
POSTLINKER = -lncurses

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${POSTLINKER}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS}

CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -Werror=vla -MMD
EXEC = tictactoe
OBJECTS = main.o game.o board.o subject.o textobserver.o strategy.o level1.o level2.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

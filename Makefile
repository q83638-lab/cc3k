CXX = g++-5
CXXFLAGS = -g -std=c++14 -Wall -MMD -Werror=vla
#CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla
EXEC = cc3k+
OBJECTS = main.o chamber.o character.o enemy.o floor.o gold.o item.o player.o potion.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

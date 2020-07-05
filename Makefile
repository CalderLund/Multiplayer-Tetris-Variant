CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla
EXEC = biquadris
OBJECTS = main.o interpreter.o game.o player.o grid.o cell.o block.o normal.o levelheavy.o blind.o specheavy.o specaction.o lock.o iblock.o jblock.o tblock.o oblock.o zblock.o lblock.o sblock.o level0.o level1.o level2.o level3.o level4.o level5.o window.o 
DEPENDS = ${OBJECTS:.o=.d}
LDFLAGS = -L/opt/X11/lib -lX11

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${LDFLAGS}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

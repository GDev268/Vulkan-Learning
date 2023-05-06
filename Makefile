COMPILER = g++
CFLAGS = -std=c++17 -O3 -Wall -fPIC -g -w
CLIBS = -lvulkan -lglfw
SOURCE = *.cpp *.hpp *.h
DEFINES = -DNDEBUG

all: ${EXSOURCE}
	${COMPILER} ${DEFINES} ${INCLUDE} ${SOURCE} ${CFLAGS} ${CLIBS} -o main; 

windows: ${EXSOURCE}
	${COMPILER} ${DEFINES} ${INCLUDE} ${SOURCE} ${CFLAGS} ${CLIBS} -o main.exe; 

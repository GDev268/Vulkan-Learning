COMPILER = g++
CFLAGS = -O3 -Wall -fPIC -g -w
CLIBS = -lvulkan -lGL -lGLU -lglfw -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ldl -lXinerama -lXcursor
SOURCE = *.cpp
DEFINES = -DNDEBUG

all: ${EXSOURCE}
	${COMPILER} ${DEFINES} ${INCLUDE} ${SOURCE} ${CFLAGS} ${CLIBS} -o main; 

windows: ${EXSOURCE}
	${COMPILER} ${DEFINES} ${INCLUDE} ${SOURCE} ${CFLAGS} ${CLIBS} -o main.exe; 

# Eron Ristich
# 7/19/2022

OBJS = gg1-c5-handler.o cspline.o perlin.o superquadric.o handler.o kernel.o main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
LDLIBS = -Llib -lmingw32 -lopengl32 -lSDL2_ttf -lglew32 -lglu32 -lfreeglut -lSDL2main -lSDL2 -lSDL2_image -lglew32mx -lassimp.dll
INC = -Iinclude

main.exe : $(OBJS)
	$(CC) $(LFLAGS) $(INC) $(OBJS) -o main.exe $(LDLIBS)

cspline.o : GG1-C5/src/perlin/cspline/cspline.h GG1-C5/src/perlin/cspline/cspline.cpp
	$(CC) $(CFLAGS) $(INC) GG1-C5/src/perlin/cspline/cspline.cpp

perlin.o : GG1-C5/src/perlin/perlin.h GG1-C5/src/perlin/cspline/cspline.h GG1-C5/src/perlin/perlin.cpp
	$(CC) $(CFLAGS) $(INC) GG1-C5/src/perlin/perlin.cpp

superquadric.o : GG1-C5/src/perlin/superquadric.h GG1-C5/src/perlin/perlin.h GG1-C5/src/perlin/superquadric.cpp
	$(CC) $(CFLAGS) $(INC) GG1-C5/src/perlin/superquadric.cpp

kernel.o : util/kernel/kernel.h util/kernel/kernel.cpp
	$(CC) $(CFLAGS) $(INC) util/kernel/kernel.cpp

handler.o : util/kernel/kernel.h util/handler.h util/handler.cpp
	$(CC) $(CFLAGS) $(INC) util/handler.cpp

gg1-c5-handler.o : util/handler.h util/kernel/kernel.h GG1-C5/src/perlin/superquadric.h GG1-C5-handler.h GG1-C5-handler.cpp
	$(CC) $(CFLAGS) $(INC) GG1-C5-handler.cpp

main.o : GG1-C5/src/perlin/cspline/cspline.h util/kernel/kernel.h util/handler.h GG1-C5-handler.h main.cpp
	$(CC) $(CFLAGS) $(INC) main.cpp

clean:
	\rm *.o *~ main.exe

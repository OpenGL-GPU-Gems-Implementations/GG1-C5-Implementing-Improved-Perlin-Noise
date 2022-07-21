# Eron Ristich
# 7/19/2022

OBJS = handler.o kernel.o main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
LDLIBS = -Llib -lmingw32 -lopengl32 -lSDL2_ttf -lglew32 -lglu32 -lfreeglut -lSDL2main -lSDL2 -lSDL2_image -lglew32mx -lassimp.dll
INC = -Iinclude

main.exe : $(OBJS)
	$(CC) $(LFLAGS) $(INC) $(OBJS) -o main.exe $(LDLIBS)

kernel.o : kernel/kernel.h kernel/kernel.cpp
	$(CC) $(CFLAGS) $(INC) kernel/kernel.cpp

handler.o : handlers/handler.h handlers/handler.cpp
	$(CC) $(CFLAGS) $(INC) handlers/handler.cpp

main.o : kernel/kernel.h handlers/handler.h main.cpp
	$(CC) $(CFLAGS) $(INC) main.cpp

clean:
	\rm *.o *~ main.exe

#Compiler
CC= g++

#Simple DirectMedia Layer library
LFLAGS=-lSDL2 -lSDL2_ttf -lSDL2_image

SRC_FILES=Bullet.cpp Game.cpp GUI.cpp Level2.cpp Level3.cpp Message.cpp Player.cpp Scene.cpp Score.cpp Object.cpp main.cpp

all:build

build:
	$(CC) $(SRC_FILES) -o bunny $(LFLAGS)

clean:
	rm bunny

#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "Player.h"
#include "GUI.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <math.h>


class Enemy: public Player
{
    protected:

        uint8_t points;

    public:

        Enemy();

        void loadData(string filepath); // followed path, distances, hp, etc...

        void movePath();
        void moveTo();
        void attack();


        ~Enemy();


};


#endif // ENEMY_H_INCLUDED

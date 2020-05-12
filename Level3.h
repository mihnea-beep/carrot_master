#ifndef LEVEL3_H
#define LEVEL3_H
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
using namespace std;
#include "Player.h"
#include "Scene.h"
#include "Score.h"
#include <stdio.h>
//#include "..\Game.h"


class Level3 : public Scene
{

  enum menuOptions
  {
      start_option,
      options_option,
      exit_option,
      no_option,
  };

  enum direction
  {
      left,
      right,
      up,
      down,
      none
  };

    direction bdir, last_pressed;

    bool start_optionsMenu;

    menuOptions menu_opt;

    bool Level3_won = false;
    Score gameScore;

    uint8_t l = 0, r = 0, u = 0, d = 0;

    Player MC;

    uint8_t tick;

    uint32_t time1, time2;

    uint32_t timer1, timer2;
    bool switch_direction = false;

    //bdir = left;

    bool bg_set = false, score_set = false;

    Player bg;

    uint8_t speed = 3;

    uint32_t delay;

    SDL_Point* vec;


    public:

        Level3();

        void draw(Player&, int, int, SDL_Renderer*);

        void render(SDL_Renderer*);

        void checkInput(SDL_Renderer*);

        void animate(Player&p, int frames_no, string frame_name, SDL_Renderer*);

        void update(SDL_Renderer*);

        void loop(SDL_Renderer*);

        void loadRes(SDL_Renderer*);

        void loadScene(SDL_Renderer*);

        void Init(SDL_Renderer* Renderer);

        void quit();

        void free();

        void movePlayer(Player&, SDL_Renderer*);



        ~Level3();

};

#endif // Level3_H
/*
#ifndef LEVEL3_H
#define LEVEL3_H


class Level3
{
    public:
        Level3();
        virtual ~Level3();

    protected:

    private:
};

#endif // LEVEL3_H
/*/

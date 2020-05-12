#ifndef LEVEL2_H
#define LEVEL2_H
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
using namespace std;
#include "Player.h"
#include "Scene.h"
#include "Score.h"
#include "Bullet.h"
//#include "..\Game.h"


class Level2 : public Scene
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

    bool level2_won = false;
    Score gameScore;

    uint8_t l = 0, r = 0, u = 0, d = 0;


    uint8_t tick;

    uint32_t time1, time2;

    //bdir = left;

    bool bg_set = false, score_set = false, winTrigger = false;

    Player bg;

    Player MC;

    uint8_t speed = 3;

    uint32_t delay;

    Bullet bullet;

    string bd; // bullet direction
    string ammo_type;

    Player* enemies = NULL;
    Player* test = NULL;
    Bullet* bullets = NULL;
    Player* dummies = NULL;
    bool clear_stage = false;
    uint8_t enemies_amount;

    int i = 0;
    int xi = 0;

    bool _test = false;

    public:

        Level2();

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

        void moveBullet(Bullet&);

        bool getWinTrigger();

        void checkWinTrigger();

        bool checkCollision(Player&, Player&);

        void moveEnemyRand(Player&, Player&, SDL_Renderer* Renderer);

        void moveEnemies(SDL_Renderer*);



        ~Level2();

};

#endif // LEVEL2_H

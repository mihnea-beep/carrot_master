#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Player.h"
#include <SDL2/SDL_ttf.h>
//#include "Message.h"
#include "Score.h"
#include "GUI.h"
#include <vector>
#include "Scene.h"
#include "Level2.h"
#include "Level3.h"
using namespace std;


class Game
{

  SDL_Window* Window = NULL;

  SDL_Renderer* Renderer = NULL;

  SDL_Surface* ScreenSurface = NULL;

  SDL_Surface* CurrentBackground = NULL;

  SDL_Rect screen;

  SDL_Surface* cursor_surface = NULL;

  SDL_Cursor *cursor = NULL;

  //const Uint8* keyState;

  bool quit = false;

  bool running = true;

  uint8_t tick;
  uint32_t timer_begin, timer_end, delay;

  int count;

  int frameCount, timerFPS, lastFrame;

  unsigned int LEVEL_NO;

  Player MC, guard, bg;

  Player rabbit, chaser;

  Player chs1, chs2, chs3;

  Player dummy;

  //new class for bullet

  Player bullet;

  bool isAlive = 0;

  bool hasDied = false;

  uint8_t bdir = left;

  bool launched;

  int bdir_f = left;

  int current_dir;

  //

 // Uint8 keyState

 /* vector<Player> chs;

  Player* enemies;*/

  uint8_t l = 0, r = 0, u = 0, d = 0;

  bool carrot_pickup = 0;

  Player test;

  uint8_t last_pressed;

  bool bg_set = 0;

  bool player_set = 0;

  bool obj_set = 0;

  int speed = 3;

  int dst = 40;

  int dst_def = 40;

  bool attacking = false;

  //Message Score;

  Score gameScore;

  bool fullscreen_toggle = 0;

  enum direction
  {
      left,
      right,
      up,
      down,
      none
  };

  // MENU // //////////////////////

  Message welcome, welcomef;

  int time1, time2, time3;

  int switch_welcome;

  Message options_1;

  GUI startBox;
  GUI optionsBox;
  GUI exitBox;

  //GUI returnBox;

  enum menuOptions
  {
      start_option,
      options_option,
      exit_option,
      no_option,
  };

  enum gameOptions
  {
    //start_game,
    //quit_game,
  //  pause_game
  };

  menuOptions menu_opt;

  gameOptions game_opt;

  bool level_start = false;

  int click;

  bool Win_Ren = false;

  bool app_running = true;

  bool start_game = false;

  bool start_optionsMenu = false;

  bool sdl_init = false;

  bool font_init = false;

  bool test_ = false;

  bool title_set = false;

  bool menu_set = false;

  bool image_init = false;

  bool score_set = false;

  bool cursor_init = false;

  bool options_title_set = false;

  bool options_set = false;

  bool options_running = false;

  GUI optionsBox1;

  GUI returnBox;

  GUI Box;

  bool win_trigger = false;

  bool returnBox_init = false;

  int string_pos = 0;
  int string_len = 0;

  Scene scene1;

  Level2 level_2;

  Level3 level_3;

  bool lvl2 = false;

  bool lvl3 = false;

  bool lvl2_init = false;

public:

    Game();

    void Init();

    void draw(Player& p);

    void draw(Player&p, int w, int h);

    void animate (Player&p, int frames_no, string frame_name);

    void drawBg(Player& p);

    void move(Player& p);

    void animate(Player& p);

    void animateGuard(Player& p);

    void updateScore(Score& s);

    bool checkCollision(Player& p1, Player& p2);

    void resetInput();

    void loadMenu();

    void loadLevel();

    void setVideoMode(bool fullscreen);

    void play();

    void moveEnemy(Player& p, int sx, int sy);
    void moveEnemyTo(Player& p, Player& i);
    void moveEnemyRand(Player& p, Player& dummy);
    void explode();

    void checkMenuInput();
    void renderMenu();
    void updateMenu();
    void quitMenu();
    void menuInit();
    void checkMenuOptions();

    void optionsMenuInit();
    void checkOptionsMenuInput();
    void updateOptionsMenu();
    void renderOptionsMenu();
    void loopOptionsMenu();
    void loadOptionsMenu();


    void CreateWindowAndRenderer();
    void freeLevel();


    void loop();
    void checkInput();
    void updateGame();
    void render();

    //TODO: Put font in a separate class

    //void draw(SDL_Rect& msg);

    ~Game();








};

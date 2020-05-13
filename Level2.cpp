#include "Level2.h"
#include "Player.h"
#include "Constants.h"
#include <sstream>
#include <math.h>
#include <iostream>
#include <cstdlib>
using namespace std;

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

Level2::Level2()
{
    //ctor
}

void Level2::movePlayer(Player& p, SDL_Renderer* Renderer)
{
  if(l)   //Movement
  {
      p.setX(p.getX()-speed);
      animate(p, 3, "bunny", Renderer);
      //last_pressed = l;
      //l = 0;
  }
  if(r)
  {
      p.setX(p.getX()+speed);
      animate(p, 3, "bunny_r", Renderer);
      //r = 0;
      //last_pressed = r;
  }
  if(u)
  {
      p.setY(p.getY()-speed);

      animate(p, 3, "bunny_u", Renderer);
      //last_pressed = u;
      //u = 0;
  }
  if(d)
  {
      p.setY(p.getY()+speed);

      animate(p, 3, "bunny_d", Renderer);
      //last_pressed = d;
      //d = 0;
  }
}

void Level2::moveBullet(Bullet& bullet)
{
  if(bullet.lifestatus())
    { // bullet function
        if(bullet.getLaunch())
      {
        bullet.setPos(MC.getX(), MC.getY());
        bullet.setLaunch(false);
        //bullet.setDir(bullet.getDir());
        bullet.setDir(bd);

      }

      if(bullet.getDir() == right)
          {

          bullet.setPos(bullet.getX() + 5, bullet.getY());
              //bullet.getDir() = right;
          }
      if(bullet.getDir() == left)
      {
      bullet.setPos(bullet.getX() - 5, bullet.getY());
      }
      if(bullet.getDir() == up)
      {
      bullet.setPos(bullet.getX(), bullet.getY() - 5);
      }
      if(bullet.getDir() == down)
      {
      bullet.setPos(bullet.getX(), bullet.getY() + 5);
      }


      if(bullet.getX() >= SCREEN_WIDTH)
          bullet.setLife(false);

      if(bullet.getX() + 32 <= 0)
                bullet.setLife(false);

      if(bullet.getY() >= SCREEN_HEIGHT)
        bullet.setLife(false);

      if(bullet.getY() + 32 <= 0)
        bullet.setLife(false);

        // temporary collision bullet enemies

      for(int i = 0; i < enemies_amount; i++)
        if(checkCollision(bullet, enemies[i]))
        {
          bullet.setLife(false);
          enemies[i].die();
          gameScore.Increment();
        }


    }
}

void Level2::moveEnemies(SDL_Renderer* Renderer)
{//temp
  int a = 0;
  //if enemies alive + if enemies not deleted
  for(int i = 0; i < enemies_amount; i++)
  {
    if(enemies[i].lifestatus())
      moveEnemyRand(enemies[i], dummies[i], Renderer);

    //temp
    if(enemies[i].lifestatus())
      a++;

  }

  if(!a)
    for(int i = 0; i < enemies_amount; i++)
      enemies[i].setLife(true);
}


void Level2::checkWinTrigger()
{
  if(gameScore.getScore() > 1)
    {
      winTrigger = true;
      setRunning(false);
    }

}

void Level2::update(SDL_Renderer* Renderer)
{

  tick++;
  movePlayer(MC, Renderer);
  for(int i = 0; i < enemies_amount; i++)
    moveBullet(bullets[i]);

  moveEnemies(Renderer);

  checkWinTrigger();

}

void Level2::animate(Player& p, int frames_no, string frame_name,
                    SDL_Renderer* Renderer)
{
    vector<string> frames(frames_no); //amount of frames can be set in player?

    for(int i = 0; i < frames_no; i++)
        frames[i] = res_path + frame_name + patch::to_string(i) + ".png";


    p.setImage(frames[(tick/5) % (frames_no)], Renderer); // /10
}

bool Level2::getWinTrigger()
{
  return winTrigger;
}


Level2::~Level2()
{
    //dtor
}



void Level2::loop(SDL_Renderer* Renderer)
{
  while(getRunning())
  {
     //time
    time1 = SDL_GetTicks();
    checkInput(Renderer);
    update(Renderer); // deleting after update doesn't work! :D FUK yes it does!
    render(Renderer);
    time2 = SDL_GetTicks();

    delay = 33 - (time2 - time1);

    delay = delay > 33 ? 0 : delay;

    SDL_Delay(delay);

  }

  quit();

}

void Level2::quit()
{// here too FUK
  delete[] enemies; // it works here but not in free() FUK good
  delete[] dummies;

  free();
//  delete[] enemies; // here too, with no testing :D FUK good
}

void Level2::free() // deleting in free doesn't work :D FUK
{
  //delete [] enemies; doesn't work like this
/*  if(_test)
    {
      delete[] enemies; // however, it works like this everywhere no questions asked
      _test = false;
    }*/
  bg_set = false;
  bg.Free();
  gameScore.Free();
  MC.Free();

  score_set = false;


  }


  //if(enemies != NULL)
    //delete[] enemies;


/*void Level2::checkScore()
{

  gameScore.Increment();
}
*/
void Level2::loadRes(SDL_Renderer* Renderer)
{
  Init(Renderer);

    if(!bg_set)
    { //l = r = d = u = 0;
      bg.setImage("Assets/space.png", Renderer);
      if(bg.getTexture() == NULL)
        cout<<"yep";
      bg.setPos(0, 0);
      bg_set = true;
      //if(bg.getTexture() == NULL)
      MC.setImage("Assets/bunny_u0.png", Renderer, 1);
      //if(MC.getTexture() == NULL)
        //cout<<"AAA";
      MC.randSpawn();
      MC.setLife(true);
      bullet.setImage("Assets/bullets/m2b0.png", Renderer);
      //if(bullet.getTexture() == NULL)
        //cout<<"nope";
      bullet.setPos(MC.getX(), MC.getY());
      bullet.setLife(false);
      enemies_amount = 10;
      clear_stage = false;
    //  ammo_type = "bullets/net1_b0.png";
      ammo_type = "bullets/net1_b";
      //bullets = new Bullet[1];
    //  for(int i = 0; i < 10; i++)
      //  bullets[i].setImage("bunny0.png", Renderer);

    //  bullets[0].setImage("bunny0.png", Renderer);
      //bullets[1].setImage("bunny_u0.png", Renderer);

      enemies = new Player[enemies_amount];
      dummies = new Player[enemies_amount];
      bullets = new Bullet[enemies_amount];
      //delete[] enemies;
      //enemies = NULL;
      //enemies = new Player[10];
      for(int i = 0; i < enemies_amount; i++)
      {
      //  enemies[i] = new Player;
        enemies[i].setImage("bunny0.png", Renderer);
        enemies[i].setLife(true);
        enemies[i].randSpawn();
        dummies[i].setLife(true);
        dummies[i].randSpawn();
        bullets[i].setLife(false);
        //bullets[i].setImage(ammo_type, Renderer);
      }

      //test = new Player[10];

      //for(int i = 0; i < 10; i++)
      //{
      //  test[i].setImage("bunny0.png", Renderer);
      //}

    //  delete [] enemies;

    }

    if(!score_set)
      {
  		gameScore.setColor(0, 0, 100);
  		gameScore.setText("Score: 0", "ChunkFive-Regular.otf", 24, Renderer);
  		score_set = true;
  	}



}

void Level2::Init(SDL_Renderer* Renderer)
{
  if(!getRunning())
    setRunning(true);
}

void Level2::loadScene(SDL_Renderer* Renderer)
{
    loadRes(Renderer);
    loop(Renderer);
}


void Level2::draw(Player &p, int w, int h, SDL_Renderer* Renderer)
{

  SDL_Rect dest;

  dest.x = p.getX();
  dest.y = p.getY();

  dest.w = w; // player tile size
  dest.h = h; //

  SDL_RenderCopy(Renderer, p.getTexture(), NULL, &dest);
}

void Level2::render(SDL_Renderer* Renderer)
{

  //Scene::render(Renderer);
  SDL_SetRenderDrawColor(Renderer, 0, 80, 100, 100);
  SDL_RenderClear(Renderer);



  draw(bg, 640, 480, Renderer);
  draw(MC, PLAYER_TILE_W, PLAYER_TILE_H, Renderer);



  for(int i = 0; i < enemies_amount; i++)
  {
    if(!clear_stage)
      if(enemies[i].lifestatus())
        draw(enemies[i], PLAYER_TILE_W, PLAYER_TILE_H, Renderer);
    //if(test[i].lifestatus())
      //draw(test[i], PLAYER_TILE_W, PLAYER_TILE_H, Renderer);
  }

  for(int i = 0; i < enemies_amount; i++)
    if(bullets[i].lifestatus())
      {
        draw(bullets[i], 14, 14, Renderer);
        animate(bullets[i], 4, ammo_type, Renderer);
      }


  gameScore.add(Renderer);
  gameScore.display(500, 10 , 96, 48, Renderer);


  SDL_RenderPresent(Renderer);

}


void Level2::checkInput(SDL_Renderer* Renderer)
{

  SDL_Event ev;


      while(SDL_PollEvent(&ev) != 0)
      {
         // cout<<"Polling events!"<<endl;

          if(ev.type == SDL_QUIT)
             {
                 cout<<"User pressed 'exit'!";
                 menu_opt = no_option;
                 setRunning(false);
                 start_optionsMenu = false;

                 //freeLevel();
                 //app_running = false;
             }

          if(ev.type == SDL_KEYDOWN)
          {

              switch(ev.key.keysym.sym)

              {

                  case SDLK_ESCAPE:
                  {
                      menu_opt = no_option;
                      setRunning(false);
                      start_optionsMenu = false;
            					free();
                      break;


                  }

                  case SDLK_PRINTSCREEN:
                      {
                          SDL_Surface* prtsc = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
                          SDL_RenderReadPixels(Renderer, NULL, SDL_PIXELFORMAT_ABGR4444, prtsc->pixels, prtsc->pitch);
                          SDL_SaveBMP(prtsc, "prnt.bmp");
                          SDL_FreeSurface(prtsc);

                          break;
                      }


                  case SDLK_SPACE:
                  {

                    if(!bullets[i].lifestatus())
                    {
                      bullets[i].setLife(true);
                      bullets[i].setLaunch(true);
                    }

                    i++;

                    if(i > enemies_amount)
                      i = 0;
                      break;
                  }

              case SDLK_h:
                  {
                    if(!clear_stage)
                      //delete[] enemies;
                        clear_stage = true;
                        _test = true;
                        //if no bullet is on screen or
                        //if there are bullets on screen, don't change them too
                        ammo_type = "bullets/rbullet";


                  //  delete[] bullets;
                    //  bullets[10].setLife(true);
                      //cout<<"Enter code:";
                      //int x;
                      //cin>>x;
                      //gameScore.setScore(x);
                      //for(int i = 0; i < 10; i++)
                      //  enemies[i].Free();
                        //enemies[i].setLife(false);
                      //delete [] enemies;
                      //enemies = NULL;
                      //enemies = NULL;
                  //    delete [] bullets;
                    //  delete [] test;

                      //clear_stage = true;


                    //  delete [] enemies;

                      break;
                  }

                  case SDLK_LEFT:
                  case SDLK_a: //left
                      {
                          l = 1;
                          r = 0;

  						bdir = left;

                          break;
                      }
                  case SDLK_RIGHT:
                  case SDLK_d: //right
                      {
                          r = 1;
                          l = 0;

  						bdir = right;


                          break;
                      }
                  case SDLK_UP:
                  case SDLK_w:
                      {
                          u = 1;
                          d = 0;

  						bdir = up;

                          break;
                      }
                  case SDLK_DOWN:
                  case SDLK_s:
                      {
                          u = 0;
                          d = 1;

  						bdir = down;

                          break;
                      }

                  default:

                      break;

              }
          }



          if(ev.type == SDL_KEYUP)
          {

              switch(ev.key.keysym.sym)

              {
                  case SDLK_LEFT:
                  case SDLK_a: //left
                      {
                          l = 0;
                          last_pressed = left;
                          //bdir = left;
                          break;
                      }
                  case SDLK_RIGHT:
                  case SDLK_d: //right
                      {

                          r = 0;
                          last_pressed = right;
                          //bdir = right;

                          break;
                      }
                  case SDLK_UP:
                  case SDLK_w:
                      {
                          u = 0;
                          last_pressed = up;
                          //bdir = up;


                          break;
                      }
                  case SDLK_DOWN:
                  case SDLK_s:
                      {
                          d = 0;
                          last_pressed = down;
                          //bdir = down;



                          break;
                      }

                  case SDLK_SPACE:
                      {

                        //  attacking = false;

                          break;
                      }

                  default:

                      last_pressed = none;

                      break;

              }


              if(last_pressed == left)
  			{
  				animate(MC, 1, "bunny", Renderer);
  				//bdir = left;
  			}

              if(last_pressed == right)
  			{
  				animate(MC, 1, "bunny_r", Renderer);
  				//bdir = right;
  			}

              if(last_pressed == up)
                  animate(MC, 1, "bunny_u", Renderer);

              if(last_pressed == down)
                  animate(MC, 1, "bunny_d", Renderer);
          }

      }

      //////////////////////////
     const Uint8* keystate = SDL_GetKeyboardState(0);

             if(keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D])
             {
                 //bullet.setDir("right");
                 bd = "right";
                 //r = 1; l = 0;
                 //animate(MC, 3, "bunny_r", Renderer);
             }

             if(keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A])
             {
                 //bullet.setDir("left");
                 bd = "left";
                 //l = 1; r = 0;
                 //animate(MC, 3, "bunny", Renderer);
             }
             if(keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_W])
             {
                 //bullet.setDir("up");
                 bd = "up";
                 //u = 1; d = 0;
                 //animate(MC, 3, "bunny_u", Renderer);
             }
             if(keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_S])
             {
              //   bullet.setDir("down");
              bd = "down";
                // u = 0; d = 1;
                 //animate(MC, 3, "bunny_d", Renderer);
             }


  }


void Level2::moveEnemyRand(Player& p, Player& dummy, SDL_Renderer* Renderer)
  {
  	int p_x1 = rand() % 600;
  	int p_y1 = rand() % 400;


    int x = dummy.getX();// + rand() % 600;
    int y = dummy.getY();// + rand() % 400;

  	float dstx = x - p.getX();
  	float dsty = y - p.getY();

  	float dist = sqrt( (dstx * dstx) + (dsty * dsty) );

  	float dirx = dstx / dist;
  	float diry = dsty / dist;

  	if(dstx < 0)
          animate(p, 3, "bunny", Renderer);
      else
          animate(p, 3, "bunny_r", Renderer);

  	p.setX(p.getX() + dirx * 1.5);

    p.setY(p.getY() + diry * 1.5);

    if(dist < 100)
    {
      dummy.randSpawn();

      //dstx += rand() % 600;
      //dsty += rand() % 400;
    }



  	/*if(checkCollision(p, dummy))
  		dummy.randSpawn();*/
  }

bool Level2::checkCollision(Player& p1, Player& p2)
  {
    /*
      if( (p1.getX() >= p2.getX() - 10) && (p1.getX() <= p2.getX() + 40) ) // +/- boundaries/masks? separate variables, not hardcoded

          if( (p1.getY() >= p2.getY() - 40) && (p1.getY() <= p2.getY() + 40) )*/

          float dstx = p2.getX() - p1.getX();
        	float dsty = p2.getY() - p1.getY();

        	float dist = sqrt( (dstx * dstx) + (dsty * dsty) );

          if(dist < 20)

             return 1;

      return 0;

  }



//}

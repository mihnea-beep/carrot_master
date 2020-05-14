#include "Level3.h"
/*
Level3::Level3()
{
    //ctor
}*/
//#include "Level3.h"
#include "Player.h"
#include "Constants.h"
#include <sstream>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <cstdlib>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

Level3::Level3()
{
    //ctor
}

void Level3::movePlayer(Player& p, SDL_Renderer* Renderer)
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

void Level3::update(SDL_Renderer* Renderer)
{

  tick++;
  movePlayer(MC, Renderer);

//  if(!switch_direction)

    timer2 = SDL_GetTicks();

    if(timer2 >= timer1 + 2000)
    {
      if(!switch_direction)
        {
          l = 0;
          r = 1;
          switch_direction = true;
        }
      else
      {
        l = 1;
        r = 0;
        switch_direction = false;
      }

      timer1 = timer2;
    }



}

void Level3::animate(Player& p, int frames_no, string frame_name,
                    SDL_Renderer* Renderer)
{
    vector<string> frames(frames_no); //amount of frames can be set in player?

    for(int i = 0; i < frames_no; i++)
        frames[i] = res_path + frame_name + patch::to_string(i) + ".png";


    p.setImage(frames[(tick/5) % frames_no], Renderer); // /10
}


Level3::~Level3()
{
    //dtor
}

void Level3::loop(SDL_Renderer* Renderer)
{
  while(getRunning())
  {
     //time
    time1 = SDL_GetTicks();
    checkInput(Renderer);
    update(Renderer);
    render(Renderer);
    time2 = SDL_GetTicks();

    delay = 33 - (time2 - time1);

    delay = delay > 33 ? 0 : delay;

    SDL_Delay(delay);

  /*  if((1000 / 60) > time2 - time1)
      SDL_Delay(1000 / 60 - (time2 - time1));*/
    //time
  }

  quit();

}

void Level3::quit()
{
  delete[] vec;
  free();
}

void Level3::free()
{
  bg_set = false;
  bg.Free();
  gameScore.Free();
  score_set = false;
  MC.Free();
}

void Level3::loadRes(SDL_Renderer* Renderer)
{
  Init(Renderer);

    if(!bg_set)
    { bg.setImage("Assets/grass_3.png", Renderer);
      bg.setPos(0, 0);
      bg_set = true;
      MC.setImage("Assets/bunny0.png", Renderer, 1);
      MC.randSpawn();
      MC.setLife(true);
      timer1 = SDL_GetTicks();
      vec = new SDL_Point[10000];
      for(int i = 0; i < 10000; i++)
{
  vec[i].x = rand() % 600;
  vec[i].y = rand() % 400;
}
    }

    if(!score_set)
      {
  		gameScore.setColor(0, 0, 100);
  		gameScore.setText("Score: 0", "Assets/ChunkFive-Regular.otf", 24, Renderer);
  		score_set = true;
  	}
    /*
    guard.setImage("heart1.png", Renderer);
    guard.randSpawn();
    rabbit.setImage("bunny0.png", Renderer, 1);
    rabbit.randSpawn();

    bullet.setImage("bullets/m2b0.png", Renderer);
    bullet.setPos(MC.getX(), MC.getY());
    //launched = false;
    isAlive = false;*/


}

void Level3::Init(SDL_Renderer* Renderer)
{
  if(!getRunning())
    setRunning(true);
}

void Level3::loadScene(SDL_Renderer* Renderer)
{

    loadRes(Renderer);
    loop(Renderer);
}


void Level3::draw(Player &p, int w, int h, SDL_Renderer* Renderer)
{

  SDL_Rect dest;

  dest.x = p.getX();
  dest.y = p.getY();

  dest.w = w; // player tile size
  dest.h = h; //

  SDL_RenderCopy(Renderer, p.getTexture(), NULL, &dest);
}

void Level3::render(SDL_Renderer* Renderer)
{
  //Scene::render(Renderer);
  SDL_SetRenderDrawColor(Renderer, 0, 80, 100, 100);
  SDL_RenderClear(Renderer);

  draw(bg, 640, 480, Renderer);
  draw(MC, PLAYER_TILE_W, PLAYER_TILE_H, Renderer);

  //gameScore.Increment();
  gameScore.add(Renderer);
  gameScore.display(500, 10 , 96, 48, Renderer);



    for(int i = 1; i < 10000; i++)
    {

      int mx = MC.getX();
      int my = MC.getY();
     // SDL_GetMouseState(&mx, &my);
    //  if((vec[i].x - 200) * (vec[i].x - 200) + (vec[i].y - 100) * (vec[i].y - 100) <= 100)
//    SDL_RenderDrawPoint(Renderer, vec[i].x, vec[i].y);

//    if( (vec[i].x <= mx + 100) || (vec[i].x >= mx - 100) )
    //  if( (vec[i].y <= my + 100) || (vec[i].y >= my - 100) )
    // float  dist = sqrt((vec[i].x - mx)*(vec[i].x - mx) + (vec[i].y - my) *(vec[i].y - my));
      // if(dist <= 100)
      // {
        // vec[i].x += 10;//rand() % 600;
        // vec[i].y -= 10;// rand() % 400;
      // }


    //  if(vec[i].x >= vec[i-1].x)
        vec[i].x = rand() % 640;
      //if(vec[i].y == vec[i-1].y)
        vec[i].y = rand() % 480;

    while(float  dist = sqrt((vec[i].x - mx)*(vec[i].x - mx) + (vec[i].y - my) *(vec[i].y - my)) < 100)
    {
      vec[i].x = rand() % 600;
      vec[i].y = rand() % 400;

    }


        // if(dist <= 100)
        //   {
        //     vec[i].x = rand() % 600;//+= 10;
        //      vec[i].y = rand() % 400;//-= 10;
        //   }

        SDL_RenderDrawPoint(Renderer, vec[i].x, vec[i].y);

        //SDL_RenderDrawPoints(Renderer, vec, 10000);
  }
/*
  for(int i = 0; i < 1000; i++)
    for(int k = 0; k < 1000; k++)
        {
          float dist = sqrt((vec[i].x - vec[k].x)*(vec[i].x - vec[k].x) + (vec[i].y - vec[k].y) *(vec[i].y - vec[k].y));
          if(dist <= 100)
          {
            vec[i].x += 10;
            vec[i].y -= 10;
          }

        }
*/


  SDL_RenderPresent(Renderer);
}


void Level3::checkInput(SDL_Renderer* Renderer)
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
                      //MC.attack(Renderer);
                  /*    if(!isAlive)
                      {   attacking = true;
                          isAlive = true;
  						            launched = true;
                      }*/ /// bullet ////
                      break;
                  }

              case SDLK_h:
                  {
                      cout<<"Enter code:";
                      int x;
                      cin>>x;
                      gameScore.setScore(x);
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
    /*  const Uint8* keystate = SDL_GetKeyboardState(0);

             if(keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D])
             {
                 bdir = right;
                 r = 1; l = 0;
                 animate(MC, 3, "bunny_r", Renderer);
             }

             if(keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A])
             {
                 bdir = left;
                 l = 1; r = 0;
                 animate(MC, 3, "bunny", Renderer);
             }
             if(keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_W])
             {
                 bdir = up;
                 u = 1; d = 0;
                 animate(MC, 3, "bunny_u", Renderer);
             }
             if(keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_S])
             {
                 bdir = down;
                 u = 0; d = 1;
                 animate(MC, 3, "bunny_d", Renderer);
             }*/


  }



//}

/*Level3::~Level3()
{
    //dtor
}*/

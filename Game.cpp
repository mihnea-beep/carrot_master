#include "Game.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "Constants.h"
#include <SDL2/SDL_ttf.h>
#include "Score.h"
#include <sstream>
#include <math.h>
//#include "include/Level2.h"
#include "Level2.h"
using namespace std;
//using namespace patch;

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

using namespace std;

void Game::Init()
{

    time3 = SDL_GetTicks();
    //SDL_Init(SDL_INIT_EVERYTHING);
    level_start = false;

	if(!image_init)
    {
		IMG_Init(IMG_INIT_PNG);
		image_init = true;
	}

	if(!font_init)
	{
		TTF_Init();
		font_init = true;
	}
/*
    if(!fullscreen)

        Window = SDL_CreateWindow("Carrot Master",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  640, 480,
                                  SDL_WINDOW_BORDERLESS);

    else

        Window = SDL_CreateWindow("Carrot Master",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  640, 480,
                                  SDL_WINDOW_FULLSCREEN);
*/

    //Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    running = true;

    //Player* player = new Player("Xyla", "player.png", 50, 50, Renderer);

    //background

    if(!bg_set)

    {
      bg.setImage("grass_3.png", Renderer);
      bg.setPos(0, 0);
      bg_set = true;
    }

    if(!player_set)

    {
        //MC.randSpawn();
        MC.setImage("bunny0.png", Renderer, 1);
        MC.randSpawn();
        guard.setImage("heart1.png", Renderer);
        guard.randSpawn();
        rabbit.setImage("bunny0.png", Renderer, 1);
        rabbit.randSpawn();
        chaser.setImage("bunny0.png", Renderer);
        chaser.randSpawn();

        bullet.setImage("bullets/m2b0.png", Renderer);
        bullet.setPos(MC.getX(), MC.getY());
        //launched = false;
        isAlive = false;

        chs1.setImage("bunny0.png", Renderer, 1);
        chs1.randSpawn();

        guard.setLife(true);
        MC.setLife(true);
        rabbit.setLife(true);
        chaser.setLife(true);
        chs1.setLife(true);



        //chs2.setImage("bunny0.png", Renderer, 1);
        //chs2.randSpawn();
        //chs3.setImage("bunny0.png", Renderer, 1);
        //()chs3.randSpawn();

        //// i need operator=();
        /*
        enemies = new Player[3];

        for(int i = 0; i < 3; i++)
        {
            Player x;

            enemies[i] =
        }*/

        player_set = true;
    }
   // test.setImage("bunny2.png", Renderer, 1);

    l = 0; u = 0; r = 0; d = 0; //


    cout<<"Init()"<<endl;

    //Font should make another class like Message
	if(!score_set)
    {
		gameScore.setColor(0, 0, 100);
		gameScore.setText("Score: 0", "ChunkFive-Regular.otf", 24, Renderer);
		score_set = true;
	}

}

Game::Game()
{
//    Player Xylanthia(renderTarget, "playersprites2.png", 0, 0, 3, 4, "Xylanthia");
    /*Init();

    loop();*/


}

void Game::loop()
{
    //static int lastTime = 0; // TIMESTUFF

    while(running)
    {
        timer_begin = SDL_GetTicks();

        checkInput();
        updateGame();
        render();

        timer_end = SDL_GetTicks();

        delay = 33 - (timer_end - timer_begin);
       // if(delay > 33)
         //   delay = 0;
       // else delay = delay;
        delay = delay > 33 ? 0 : delay;
        SDL_Delay(delay);
    }
}

        /*prevTime = currentTime;
        currentTime = SDL_GetTicks();
        delta = (currentTime - prevTime) / 1000.0f;*/

void Game::checkInput()
{
    SDL_Event ev;


    while(SDL_PollEvent(&ev) != 0)
    {
       // cout<<"Polling events!"<<endl;

        if(ev.type == SDL_QUIT)
           {
               cout<<"User pressed 'exit'!";
               menu_opt = no_option;
               running = false;
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
					running = false;
          start_optionsMenu = false;
					freeLevel();
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
                    if(!isAlive)
                    {   attacking = true;
                        isAlive = true;
						            launched = true;
                    }
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

                        attacking = false;

                        break;
                    }

                default:

                    last_pressed = none;

                    break;

            }

            //Uint8* keystate = SDL_GetKeyState(0);

            //if()




            if(last_pressed == left)
			{
				animate(MC, 1, "bunny");
				//bdir = left;
			}

            if(last_pressed == right)
			{
				animate(MC, 1, "bunny_r");
				//bdir = right;
			}

            if(last_pressed == up)
                animate(MC, 1, "bunny_u");

            if(last_pressed == down)
                animate(MC, 1, "bunny_d");
        }

    }

}

void Game::updateGame()
{
    //cout<<"Updating game!"<<endl;
    tick++;

    move(MC); // Move main character

    animateGuard(guard);

    updateScore(gameScore);
/*
    if(!hasDied)
      if(gameScore.getScore() > 30)
      {
        MC.die();
        hasDied = true;
      }
*/

    if(rabbit.lifestatus())
        moveEnemy(rabbit, rabbit.getX(), rabbit.getY());
    if(chaser.lifestatus())
        moveEnemyTo(chaser, guard);
    if(chs1.lifestatus())
        moveEnemyRand(chs1, dummy);
    if(chs2.lifestatus())
        moveEnemyTo(chs2, guard);
    if(chs3.lifestatus())
        moveEnemyTo(chs3, guard);


    if(checkCollision(chaser, guard))
        guard.randSpawn();

	if(checkCollision(chs1, guard))
        guard.randSpawn();

	//if(checkCollision(chs2, guard))
        //guard.randSpawn();

//	if(checkCollision(chs3, guard))
        //guard.randSpawn();

	//if(checkCollision(chaser, chs1))
      //  chs1.randSpawn();

    if(checkCollision(chs1, MC))
    {
        if(chs1.getX() < MC.getX())
            MC.setX(MC.getX() + 40);
        else
            MC.setX(MC.getX() - 40);
    }

    if(!chs1.lifestatus())
        chs1.respawn(5000);
    if(!chaser.lifestatus())
        chaser.respawn(5000);
    if(!rabbit.lifestatus())
        rabbit.respawn(5000);
    if(!MC.lifestatus())
      MC.respawn(5000);

   /* cout<<"LEFT: "<<l<<endl;
    cout<<"RIGHT: "<<r<<endl;
    cout<<"UP: "<<u<<endl;
    cout<<"DOWN: "<<d<<endl; */
/* if level1 won, load next level

    if(gameScore.getScore() > 100)
    {
      scene1.setRunning(true);
    }

    if(scene1.getRunning())
    {
      free level1

      scene1.Init(Renderer);
      scene1.loadScene(Renderer);
    }
    */



    checkMenuOptions();

    //next level condition
    if(gameScore.getScore() > 1)
      {
        lvl2 = true;
        running = false;
        level_start = false;
        freeLevel();
      }

}

void Game::render()
{
    SDL_SetRenderDrawColor(Renderer, 126, 192, 238, 255);
    SDL_RenderClear(Renderer);

     const Uint8* keystate = SDL_GetKeyboardState(0);

            if(keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D])
            {
                bdir = right;
                r = 1; l = 0;
                animate(MC, 3, "bunny_r");
            }

            if(keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A])
            {
                bdir = left;
                l = 1; r = 0;
                animate(MC, 3, "bunny");
            }
            if(keystate[SDL_SCANCODE_UP])
            {
                bdir = up;
                u = 1; d = 0;
                animate(MC, 3, "bunny_u");
            }
            if(keystate[SDL_SCANCODE_DOWN])
            {
                bdir = down;
                u = 0; d = 1;
                animate(MC, 3, "bunny_d");
            }

    drawBg(bg);

    draw(MC);
    draw(guard);

    if(rabbit.lifestatus())
        draw(rabbit);

    if(chaser.lifestatus())
        draw(chaser);
    //draw(bullet);

    if(chs1.lifestatus())
        draw(chs1);
	//draw(chs2);
	//draw(chs3);
    //draw(test);
    //draw(messageRc);

    //

    //only shoots right

    if(attacking)
    {

        //bullet
        //SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
        //SDL_RenderDrawLine(Renderer, MC.getX(), MC.getY(), MC.getX() + 100, MC.getY());
       // if(check collision) bullet.setPos(MC.getX(), MC.getY()) --> make the bunny carry stuff
        attacking = false;                // around from a to b // pickup_item = true // itemcode or smth like that
    }

    if(isAlive)
    {
		if(launched)
        {
			bullet.setPos(MC.getX(), MC.getY());
			launched = false;
			//if(last_pressed == bdir)
              //  current_dir = last_pressed;
            //else
            //if(last_pressed == right && right = 1)
                current_dir = bdir;

		}


        //while(isAlive)
        if(current_dir == right)
            {

            bullet.setPos(bullet.getX() + 5, bullet.getY());
                //current_dir = right;
            }
		if(current_dir == left)
		{
			bullet.setPos(bullet.getX() - 5, bullet.getY());
		}
		if(current_dir == up)
		{
			bullet.setPos(bullet.getX(), bullet.getY() - 5);
		}
		if(current_dir == down)
		{
			bullet.setPos(bullet.getX(), bullet.getY() + 5);
		}

            draw(bullet);
            animate(bullet, 3, "bullets/m2b");
			//bullet.draw(Renderer);
            attacking = false;

            if(bullet.getX() >= SCREEN_WIDTH)
                isAlive = false;

			if(bullet.getX() + 32 <= 0)
                isAlive = false;

			if(bullet.getY() >= SCREEN_HEIGHT)
				isAlive = false;

			if(bullet.getY() + 32 <= 0)
				isAlive = false;

            if(checkCollision(bullet, chs1))
                {
                    isAlive = false;
                    explode();
                    chs1.die();
                    for(int i = 0; i < 10; i++)
                        gameScore.Increment();
                }

            if(checkCollision(bullet, chaser))
				{
				    isAlive = false;
				    chaser.die();
				    for(int i = 0; i < 10; i++)
                        gameScore.Increment();
				}

			if(checkCollision(bullet, rabbit))
				{
				    isAlive = false;
				    rabbit.die();
				    for(int i = 0; i < 10; i++)
                        gameScore.Increment();
				}

			//if(checkCollision(bullet, MC))
				//isAlive = false;
            //if(bullet.getY() >= SCREEN)
           // if(bullet.getX())


    }

    gameScore.add(Renderer);


    //
    gameScore.display(500, 10 , 96, 48, Renderer);

/*    if(!win_trigger)
      if(gameScore.getScore() < 0)
      {
        //GUI Box;
        Box.setDim(100, 60);
    		Box.setColor(255, 255, 255);
    		Box.setPos(SCREEN_WIDTH/2 - startBox.getW()/2, SCREEN_HEIGHT/3);
    		//Box.setMsg("Game Over!", Renderer);

        win_trigger = true;
      }*/

  //    string s = "Game Over!";
    //  string s1 = "";
/*

    time2 = SDL_GetTicks();

    if(time2 >= time3 + 2000) // see that i don't use time3 and time1 elsewhere and put this in a class
                             // and fix the time thing + color + the size (print character by character in their own space?)
      {

          for(int i = 0; i < s.length() - string_len; i++)
          {
              s1.append("  ");
          }
          Box.setMsg(s.substr(string_pos, string_len) + s1, Renderer);
          string_len ++;
          time3 = time2;

          s1 = "";
      }

      if(win_trigger)
        {
         //    Box.setMsg(s.substr(string_pos, string_len), Renderer); too fast
          //string_len ++;

          Box.displayMsg(Renderer);
          gameScore.Decrement();

        }
*/





    SDL_RenderPresent(Renderer);

}


void Game::loadLevel()
{
    Init();
    loop();
}

void Game::loadMenu()
{

    menuInit();

    //welcome.display(200, 200, 96, 48, Renderer);

    while (running)
    {

        /////////////////////
         timer_begin = SDL_GetTicks();


        checkMenuInput();
        updateMenu();
        renderMenu();
        //time2 = SDL_GetTicks();

        timer_end = SDL_GetTicks();

        delay = 33 - (timer_end - timer_begin);

        delay = delay > 33 ? 0 : delay;
        SDL_Delay(delay);
        ////////////////////
    }

    quitMenu();

}

void Game::CreateWindowAndRenderer()
{
    Window = SDL_CreateWindow("Carrot Master 0.49", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_FULLSCREEN);

    Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    Win_Ren = true;

}

void Game::freeLevel() // reset basically
{                      // could copy data to a file (savefile)
	MC.Free();          // and load from there if "Continue" button is clicked
	guard.Free();       //
	bg.Free();
	gameScore.Free();

	score_set = false;

	bg_set = false;

	player_set = false;
}


void Game::menuInit()
{

    running = true;

	if(!sdl_init)
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		sdl_init = true;
	}

    click = false;

	if(!font_init)
	{
		TTF_Init();
		font_init = true;
	}

	if(!Win_Ren)
    {
		Window = SDL_CreateWindow("Carrot Master 0.49", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

		Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

		Win_Ren = true;
	}

	if(!cursor_init) // this could go in the constructor
    {
        cursor_surface = SDL_LoadBMP("cursor.carrotz");

        if(cursor_surface == NULL )
            cout<<"error!";

        cursor = SDL_CreateColorCursor(cursor_surface, 0, 0);

        SDL_SetCursor(cursor);

        cursor_init = true;

        if(cursor_surface != NULL)
            SDL_FreeSurface(cursor_surface);
    }

    time1 = SDL_GetTicks();

	if(!title_set)
	{
		welcomef.setColor(100, 100, 0);
		welcomef.setText("Carrot Master v0.49", "ChunkFive-Regular.otf", 34, Renderer);
		welcome.setColor(255, 255, 255);
		welcome.setText("Carrot Master v0.49", "ChunkFive-Regular.otf", 34, Renderer);


		title_set = true;
	}

	switch_welcome = 0;

    if(!menu_set)
	{
		startBox.setDim(100, 60);
		startBox.setColor(255, 255, 255);
		startBox.setPos(SCREEN_WIDTH/2 - startBox.getW()/2, SCREEN_HEIGHT/3);
		startBox.setMsg("Start", Renderer);

		optionsBox.setDim(100, 60);
		optionsBox.setColor(255, 255, 255);
		optionsBox.setPos(SCREEN_WIDTH/2 - optionsBox.getW()/2, SCREEN_HEIGHT/3 + 1.5*optionsBox.getH());
		optionsBox.setMsg("Options", Renderer);

		exitBox.setDim(100, 60);
		exitBox.setColor(255, 255, 255);
		exitBox.setPos(SCREEN_WIDTH/2 - exitBox.getW()/2, optionsBox.getY() + 1.5*exitBox.getH());
		exitBox.setMsg("Quit", Renderer);

		menu_set = true;
	}



}

void Game::updateMenu()
{
    menu_opt = no_option;
    int mx;
    int my;
    SDL_GetMouseState(&mx, &my);
    /*cout<<"X: "<<mx;
    cout<<endl;
    cout<<"Y: "<<my;
    cout<<endl;*/

    //check mouse position inside menu boxes

    if( (mx >= startBox.getX()) && (mx <= (startBox.getX() + startBox.getW())) )
        if( (my >= startBox.getY()) && (my <= (startBox.getY() + startBox.getH())) )
            menu_opt = start_option;

     if( (mx >= optionsBox.getX()) && (mx <= (optionsBox.getX() + optionsBox.getW())) )
        if( (my >= optionsBox.getY()) && (my <= (optionsBox.getY() + optionsBox.getH())) )
            menu_opt = options_option;

     if( (mx >= exitBox.getX()) && (mx <= (exitBox.getX() + exitBox.getW())) )
        if( (my >= exitBox.getY()) && (my <= (exitBox.getY() + exitBox.getH())) )
            menu_opt = exit_option;


    if(menu_opt == start_option)
        {
        startBox.setColor(100, 100, 0);
       // cout<<"\a";
        }
    else
        startBox.setColor(255, 255, 255);

    if(menu_opt == options_option)
        optionsBox.setColor(100, 100, 0);
    else
        optionsBox.setColor(255, 255, 255);

    if(menu_opt == exit_option)
        exitBox.setColor(100, 100, 0);
    else
        exitBox.setColor(255, 255, 255);
}

void Game::checkMenuInput()
{
    SDL_Event ev;

    while(SDL_PollEvent(&ev))
        {
            if(ev.type == SDL_QUIT)
               {
                   cout<<"User pressed 'exit'!";
                   running = false;
                   app_running = false;
               }

            if(ev.type == SDL_MOUSEBUTTONDOWN)
            {
                if(menu_opt == start_option)
                    click = start_option;
                else
                    if(menu_opt == exit_option)
                        click = exit_option;
                    else //?? why was that, i forgot
                      if(menu_opt == options_option)
                        click = options_option;

                else
                    click = no_option;
            }

              if(ev.type == SDL_MOUSEBUTTONUP)
            {
               if(click == start_option)
                if(menu_opt == start_option)
                    {
                        running = false;
                        //level_start = true;
                        cout<<"User has pressed 'Start game'!";
                    }

                if(click == exit_option)
                    if(menu_opt == exit_option)
                    {
                        running = false;
                        cout<<"User has pressed 'Quit game'!";
                    }

                if(click == options_option)
                  if(menu_opt == options_option)
                    {
                      running = false;
                    }
            }

            if(ev.type == SDL_KEYDOWN)
        {

            switch(ev.key.keysym.sym)

            {

                case SDLK_SPACE:
                {
                    //cout<<"Fullscreen: ";

                    //cin>>fullscreen;

                    //running = false;
                    //MC.attack(Renderer);
                    attacking = false;


                    break;


                }

                default:

                    break;
            }

        }

        }
}

void Game::checkMenuOptions()
{
    if(menu_opt == no_option)
        running = false;
}

void Game::renderMenu()
{

    SDL_SetRenderDrawColor(Renderer, 0, 80, 100, 100);
    SDL_RenderClear(Renderer);

        // buttons for the menu
        //separate class

    /*if(time2 >= time1 + 3000)
     {
         if(switch_welcome)
            switch_welcome = 0;
     }*/


    if(!switch_welcome)
        welcome.display(320 - 120, 20, 220, 60, Renderer);
    else
        welcomef.display(320 - 120, 20, 220, 60, Renderer);

   // if(SDL_GetTicks() % 10)

   time2 = SDL_GetTicks();

   if(time2 >= time1 + 1500)
    {
        switch_welcome ++;
        welcomef.display(200, 20, 220, 60, Renderer);
        time1 = time2;

        if(switch_welcome >= 2)
            switch_welcome = 0;
    }


    startBox.display(Renderer);
    startBox.displayMsg(Renderer);
    optionsBox.display(Renderer);
    optionsBox.displayMsg(Renderer);
    exitBox.display(Renderer);
    exitBox.displayMsg(Renderer);


    SDL_RenderPresent(Renderer);
}

void Game::quitMenu()
{
    if(menu_opt == exit_option)
    {

        SDL_DestroyRenderer(Renderer);
        SDL_DestroyWindow(Window);
        SDL_Quit();
        app_running = false;
		cout<<"app_running: "<<app_running;
         //exit application
    }

    if(menu_opt == start_option)
	{
		//welcome.Free();
		//welcomef.Free();
		//startBox.Free();
		//optionsBox.Free();
		//exitBox.Free();
		start_game = true;//load level
    level_start = true; //

    /* free other stuff in main menu
    then procceed to switch flags and load neccessary stuff*/

		//TTF_Quit();

	}

  if(menu_opt == options_option)
  {
    running = false;
  /*  scene1.setRunning(true); // testing scene1 ---
    cout<<scene1.getRunning();
    scene1.loadScene(Renderer);*/
    start_optionsMenu = true;
  }

}

void Game::setVideoMode(bool fs)
{
    if ( (fs ==  0) || (fs == 1) )
        fullscreen_toggle = fs;
    else
        cout<<"setVideoMode must be passed a boolean!";
}

void Game::play()
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
                         "Missing file",
                         "This is a demo. Options -> Press f to toggle fullscreen\nEscape to go back\nHave fun!",
                         NULL);
    while(app_running)
   {
       loadMenu();

    if(start_optionsMenu)
        if(app_running)
            loadOptionsMenu();

       if(level_start)
	      if(app_running)
		      loadLevel();

      if(lvl2)
  //  if(level_2.getRunning())
        if(app_running)
        //  if(level_2.getRunning())
            {
              level_2.loadScene(Renderer);

              if(!level_2.getRunning())
                {
                  lvl2 = false; // an enum could work well
                }

              if(level_2.getWinTrigger())
              {
                lvl3 = true;
              }
            }

        if(lvl3)
          if(app_running)
          {
            level_3.loadScene(Renderer);

            if(!level_3.getRunning())
              lvl3 = false;

            // if level 3 win winTrigger
            // lvl 4 = true
          }

   }
}
void Game::drawBg(Player &p)
{

    SDL_Rect dest;

    dest.x = p.getX();
    dest.y = p.getY();

    dest.w = 640; // player tile size
    dest.h = 480; //

    SDL_RenderCopy(Renderer, p.getTexture(), NULL, &dest);
}

void Game::draw(Player &p)
{

    SDL_Rect dest;

    dest.x = p.getX();
    dest.y = p.getY();

    dest.w = PLAYER_TILE_W; // player tile size
    dest.h = PLAYER_TILE_H; //

    SDL_RenderCopy(Renderer, p.getTexture(), NULL, &dest);
}

void Game::draw(Player &p, int w, int h) // w and h could be loaded only once at the beginning
{

    SDL_Rect dest;

    dest.x = p.getX();
    dest.y = p.getY();

    if( l == r)
    {
        dest.w = w; // player tile size
        dest.h = h; //
    }
    else
    {
        dest.w = PLAYER_TILE_W; // player tile size
        dest.h = PLAYER_TILE_H;
    }

    SDL_RenderCopy(Renderer, p.getTexture(), NULL, &dest);
}

void Game::move(Player &MC)
{
    if(l)   //Movement
    {
        MC.setX(MC.getX()-speed);
        animate(MC, 3, "bunny");
        //last_pressed = l;
        //l = 0;
    }
    if(r)
    {
        MC.setX(MC.getX()+speed);
        animate(MC, 3, "bunny_r");
        //r = 0;
        //last_pressed = r;
    }
    if(u)
    {
        MC.setY(MC.getY()-speed);

        animate(MC, 3, "bunny_u");
        //last_pressed = u;
        //u = 0;
    }
    if(d)
    {
        MC.setY(MC.getY()+speed);
        animate(MC, 3, "bunny_d");

        //last_pressed = d;
        //d = 0;
    }

    if(MC.getX() <= -PLAYER_TILE_W) //Edges
        MC.setX(SCREEN_WIDTH);
    if(MC.getX() >= SCREEN_WIDTH + 10)
        MC.setX(-8);
    if(MC.getY() <= -PLAYER_TILE_H)
        MC.setY(SCREEN_HEIGHT);
    if(MC.getY() >= SCREEN_HEIGHT + 10)
        MC.setY(-8);

    //if(last_pressed == r)
      //      if(r != 0)
         //       animate(MC, 1, "bunny_r");


    //if(l==r==u==d==0)
        //animate(MC, 3, "bunny"); // MEMORY LEAK no more but it's not the ideal
       // animate(MC, 3, "bunny_r");                        // way to do it
}

void Game::moveEnemy(Player& p, int sx, int sy)
{
    //if(p.getX() <= dst)
    /*if(sx <= sx + dst)
        p.setPos(sx + 1, sy);*/

    //if( (p.getX() <= MC.getX() - 100)  && (p.getX() >= MC.getX() + 100) )


            float dstx = MC.getX() - p.getX();
            float dsty = MC.getY() - p.getY();
            float dstPoints = sqrt((dstx*dstx) + (dsty*dsty));

/*            cout<<"dstPoints: "<<dstPoints<<endl;
            cout<<"DIRX: "<<dirx<<" DIRY: "<<diry;*/

            if(dstPoints <= 100) // the enemy field of view

            {
                float dirx = dstx / dstPoints;
                float diry = dsty / dstPoints;

                if(p.getX() < MC.getX())
                    animate(p, 3, "bunny_r");
                else
                    animate(p, 3, "bunny");

                p.setX(p.getX() + dirx * 1.5);
                p.setY(p.getY() + diry * 1.5);
                if(checkCollision(p, MC)) // this isn't really enemy movement related
                        {
                            int mv = 10;                 // maybe move to a diff method
                            gameScore.Decrement();

                            if(dirx >= 0)
                                //for(int i = 0; i <= mv; i++)
                            //{
                                //MC.setX(p.getX() + 10);
                              //  p.setX(p.getX() - 10);
                            //}
                                MC.setX(p.getX() + 100);

                            else
                                if(dirx <= 0)
                                    MC.setX(p.getX() - 100);



                        }
            }

    /*
    if( (MC.getX() > p.getX()) && (MC.getX() <= p.getX() + 100))
        {
            p.setX(p.getX() + 1);
            animate(p, 3, "bunny_r");
        }
    else
        if( (MC.getX() < p.getX()) && (MC.getX() >= p.getX() - 100) )
    {
        p.setX(p.getX() - 1);
        animate(p, 3, "bunny");

    }*/

    // maybe some quadrants position based movement and smth when p reaches same pos as MC
   /* if(1) -----------> maths from Stackoverflow just rethink it
    {
        float dstx = MC.getX() - p.getX();
        float dsty = MC.getY() - p.getY();
        float hypotenuse = sqrt((dstx*dstx) + (dsty*dsty));

if(hypotenuse < 100){

        p.setX(p.getX() + 0.1*dstx/hypotenuse);
        p.setY(p.getY() + 0.1*dsty/hypotenuse);
}
    }*/ // ----------> maths
    else

    {


    if(dst >= 0)

    {
        p.setPos(sx + 1, sy);
        dst--;
        animate(p, 3, "bunny_r");
    }
    else
    {
        if(dst >= -dst_def)
        {
            p.setPos(sx - 1, sy);
            dst--;
            animate(p, 3, "bunny");
        }
        else
            dst = dst_def ;
    }

    }

   // cout<<dst<<endl;


   // for(int i = dst; i > 0; i--)
     //   p.setPos(sx - 1, sy);

}

void Game::moveEnemyTo(Player& p, Player& i)
{
    float dstx = i.getX() - p.getX();
    float dsty = i.getY() - p.getY();

    float dist = sqrt( (dstx * dstx) + (dsty * dsty) );

    float dirx = dstx / dist;
    float diry = dsty / dist;

    p.setX(p.getX() + dirx * 1.5);

    p.setY(p.getY() + diry * 1.5);

    // not considering up and down for now

    if(dstx > 0)
        animate(p, 3, "bunny_r");
    else
        animate(p, 3, "bunny");






}

void Game::explode()
{

}

void Game::moveEnemyRand(Player& p, Player& dummy)
{
	int p_x1 = rand() % 60;
	int p_y1 = rand() % 40;

	//float dstx = - p.getX() + MC.getX() + p_x1;
	//float dsty = - p.getY() + MC.getY() + p_y1;

	float dstx = dummy.getX() - p.getX();
	float dsty = dummy.getY() - p.getY();

	float dist = sqrt( (dstx * dstx) + (dsty * dsty) );

	float dirx = dstx / dist;
	float diry = dsty / dist;

	if(dstx < 0)
        animate(p, 3, "bunny");
    else
        animate(p, 3, "bunny_r");

	p.setX(p.getX() + dirx * 1.5);

    p.setY(p.getY() + diry * 1.5);

	if(checkCollision(p, dummy))
		dummy.randSpawn();



}

void Game::resetInput() // not great
{
    l = 0; r = 0; u = 0; d = 0;
}

void Game::animate(Player& p)
{
    vector<string> frames(3); //amount of frames can be set in player?
    frames[0] = "bunny1.png";
    frames[1] = "bunny2.png";
    frames[2] = "bunny3.png";


    p.setImage(frames[(tick/5) % 3], Renderer);
}

void Game::animate(Player& p, int frames_no, string frame_name)
{
    vector<string> frames(frames_no); //amount of frames can be set in player?

    for(int i = 0; i < frames_no; i++)
        frames[i] = frame_name + patch::to_string(i) + ".png";


    p.setImage(frames[(tick/5) % frames_no], Renderer);
}

void Game::animateGuard(Player& p) // pass the object, the number of frames and read them with
{                                  // standard format: string "obj_name" + patch::to_str(i);
    vector<string> frames(4); //amount of frames can be set in guard?
    frames[0] = "heart1.png";
    frames[1] = "heart2.png";
    frames[2] = "heart3.png";
    frames[3] = "heart4.png";


    p.setImage(frames[(tick/5) % 3], Renderer);
}

void Game::updateScore(Score &s)
{
    //condition to increment score
    //if(SDL_GetTicks() % 10 == 0)
    if(checkCollision(MC, guard))
        {
            guard.randSpawn();
            gameScore.Increment();
        }



}

/*void Game::draw(SDL_Rect& msgrc)
{

    SDL_RenderCopy(Renderer, messageTexture, NULL, &msgrc);

}*/

bool Game::checkCollision(Player& p1, Player& p2)
{
    if( (p1.getX() >= p2.getX() - 10) && (p1.getX() <= p2.getX() + 20) ) // +/- boundaries/masks? separate variables, not hardcoded

        if( (p1.getY() >= p2.getY() - 10) && (p1.getY() <= p2.getY() + 20) )

           return 1;

    return 0;

}

void Game::loadOptionsMenu()
{
  if(start_optionsMenu)
  {
    //running = true;

    optionsMenuInit();

    loopOptionsMenu();

  }

}

void Game::loopOptionsMenu()
{

  timer_begin = SDL_GetTicks();

  while(options_running)
    {
      checkOptionsMenuInput();
      updateOptionsMenu();
      renderOptionsMenu();
    }

    timer_end = SDL_GetTicks();

    delay = 33 - (timer_end - timer_begin);

    delay = delay > 33 ? 0 : delay;
    SDL_Delay(delay);
}

void Game::renderOptionsMenu()
{
  SDL_SetRenderDrawColor(Renderer, 0, 80, 100, 100);
  SDL_RenderClear(Renderer);

  options_1.display(SCREEN_WIDTH/2 - 50,
                    SCREEN_HEIGHT/5 - 50,
                    100, 50, Renderer);

  returnBox.display(Renderer);
  returnBox.displayMsg(Renderer);
  //SDL_RenderCopy(options_1.getTexture(), Renderer);
  //SDL_RenderCopy(optionsBox1.getTexture())

  SDL_RenderPresent(Renderer);

}

void Game::updateOptionsMenu()
{

}

void Game::checkOptionsMenuInput()
{
  SDL_Event ev;

  while(SDL_PollEvent(&ev))
      {
          if(ev.type == SDL_QUIT)
             {
                 cout<<"User pressed 'exit'!";

                 options_running = false;
                 level_start = false;
                 start_optionsMenu = false;

                 //running = false;
                 //app_running = false;
             }

            if(ev.type == SDL_KEYDOWN)
            {
              switch(ev.key.keysym.sym)
              {
                case SDLK_ESCAPE:

                cout<<"User pressed 'escape'!";

                options_running = false;
                start_optionsMenu = false;
                level_start = false;

                break;

                case SDLK_f:

                cout<<"Fullscreen!";
/*
                SDL_DestroyWindow(Window);
                SDL_DestroyRenderer(Renderer);

                Window = SDL_CreateWindow("Carrot Master v.49",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        640, 480,
                                        SDL_WINDOW_SHOWN);

                Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                */

                if(!fullscreen_toggle)
                    {
                        SDL_SetWindowFullscreen(Window, SDL_WINDOW_FULLSCREEN);
                        fullscreen_toggle = true;
                    }
                else
                    {
                         SDL_SetWindowFullscreen(Window, 0);
                         fullscreen_toggle = false;
                    }


                break;

                default:

                break;
              }
            }
      }
}
void Game::optionsMenuInit()
{
  options_running = true;

  if(!options_title_set)
	{
	//	welcomef.setColor(100, 100, 0);
		//welcomef.setText("Options", "ChunkFive-Regular.otf", 34, Renderer);
		options_1.setColor(255, 255, 255);
		options_1.setText("Options", "ChunkFive-Regular.otf", 34, Renderer);

    options_title_set = true;

	}

  if(!returnBox_init)
  {

        returnBox.setDim(100, 60);
        returnBox.setColor(255, 255, 255);
        returnBox.setPos(SCREEN_WIDTH/2 - returnBox.getW()/2, SCREEN_HEIGHT/3);
        returnBox.setMsg("Return", Renderer);

        returnBox_init = true;

  }


	//switch_welcome = 0;

    if(!options_set)
	{
		/*optionsBox1.setDim(100, 60);
		optionsBox1.setColor(255, 255, 255);
		optionsBox1.setPos(SCREEN_WIDTH/2 - startBox.getW()/2, SCREEN_HEIGHT/3);
    optionsBox1.setMsg("In progress ...", Renderer);*/

    options_set = true;

	}
}

Game::~Game()
{

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    cout<<"QUITTING"<<endl<<endl;
    cout<<"UPTIME: "<<SDL_GetTicks()/1000<<" seconds.";
    cout<<"SCORE: "<<gameScore.getScore();
    SDL_Quit();
}

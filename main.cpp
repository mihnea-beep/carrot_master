
//Main

#include<SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include<SDL2/SDL_image.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <cstdlib>
//#include "Player.h"
#include "Game.h"
//#include "Player.h"
//#include "resources.rc"

//Uint8 keystate;

//SDL_Getkey

//using namespace std;

#include "Constants.h"
//#include "test0000.h"

int main( int argc, char* args[] )
{

    Game CarrotMaster;
    //CarrotMaster.setVideoMode(true);

  //  if(CarrotMaster.loadMenu() == true) // arguments
    //    CarrotMaster.loadLevel();   // arguments here, data from menu

    CarrotMaster.play();

    //test a;
    //a.display();
/*
    cout<<endl<<endl<<"A:";
    Player* a;

    SDL_Renderer* Renderer;

    a = new Player[1];

    for(int i = 0; i < 1; i++)
    {
        a[i].setImage("bunny0.png", Renderer);
    }



    delete[] a;


*/
    return 0;
}

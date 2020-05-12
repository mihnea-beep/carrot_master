
#include "Message.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

using namespace std;

Message::Message()
{

}

Message::Message(SDL_Renderer* renderer, string text)
{

}

void Message::setText(string text, string font, uint16_t size, SDL_Renderer* renderer)
{
    //msg_color = {0, 0, 100};

    if(msg_font != NULL)
        TTF_CloseFont(msg_font);
    msg_font = NULL;

    //if(msg_font != NULL)
    //    delete [] msg_font;

    // maybe the surface is used right after being freed?
    // somewhere in the program

    //if(msg_surface != NULL)
     //   SDL_FreeSurface(msg_surface);

   // msg_surface = NULL;


    msg_font = TTF_OpenFont(font.c_str(), size);

	if(msg_texture != NULL)
		SDL_DestroyTexture(msg_texture);

    msg_texture = NULL;

	//if(msg_surface != NULL)
	//	SDL_FreeSurface(msg_surface);

    msg_surface = TTF_RenderText_Solid(msg_font, text.c_str(), msg_color);

    msg_texture = SDL_CreateTextureFromSurface(renderer, msg_surface);

    SDL_FreeSurface(msg_surface);

	//TTF_CloseFont(msg_font); instacrash :D

	//msg_surface = NULL; no clue what just happened
}

void Message::setColor(int r, int g, int b)
{
    msg_color = {r, g, b};
}

void Message::Free()
{
    if(msg_texture != NULL)
        SDL_DestroyTexture(msg_texture);

    msg_texture = NULL;

   // if(msg_surface != NULL)
     //   SDL_FreeSurface(msg_surface);
    //msg_surface = NULL;

  //  if(msg_font != NULL)
    //    TTF_CloseFont(msg_font);

    //msg_font = NULL;

    //if(msg_surface != NULL)
    //    SDL_FreeSurface(msg_surface);

	//if(msg_font != NULL)
	//	TTF_CloseFont(msg_font);
}

void Message::display(int x, int y, int w, int h, SDL_Renderer* renderer)
{
    msgRc.x = x;
    msgRc.y = y;
    msgRc.w = w;
    msgRc.h = h;

    SDL_RenderCopy(renderer, msg_texture, NULL, &msgRc);
}

Message::~Message()
{
    if(msg_surface != NULL)
        delete [] msg_surface;

    if(msg_texture != NULL)
        delete [] msg_texture;

    if(msg_font != NULL)
        delete [] msg_font;

}

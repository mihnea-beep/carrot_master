#ifndef MESSAGE_H
#define MESSAGE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std;

class Message
{

protected:

    TTF_Font* msg_font = NULL;

    SDL_Color msg_color = {255, 255, 255};

    SDL_Surface* msg_surface = NULL;

    SDL_Texture* msg_texture = NULL;

    SDL_Rect msgRc;

public:

    Message();

    Message(SDL_Renderer* renderer, string text);

    void setText(string text, string font, uint16_t size, SDL_Renderer* renderer);
    void display(int x, int y, int w, int h, SDL_Renderer* renderer);
    void setColor(int, int, int);

    void Free();

    ~Message();

};


#endif //

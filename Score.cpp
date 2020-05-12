#include <iostream>
#include <string>
#include <sstream>
#include <string.h>

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
#include "Score.h"

int Score::getScore()
{
    return score;
}

void Score::Increment()
{
    score++;
}

void Score::Decrement()
{
    score--;
}

void Score::Free()
{
    Message::Free();
    score = 0;
}

                // operator << ----> file output instead of console
                // final score append or in a binary + new button with highscores?
Score::~Score() // does it use the base destructor by default if it's already implemented?
{

}

void Score::add(SDL_Renderer* renderer)
{

    //string new_score = "Score: " + to_string(score); doesn't work? bugzilla smth

    //ostringstream sscore;

    //sscore << score;

    //string test = "Error";

    //cout<<score;

    string new_score = "Score: " + patch::to_string(score);

    //cout<<endl<<new_score;

    if(msg_texture != NULL)
        SDL_DestroyTexture(msg_texture); // **** LAST ADDED THING **** WHAT WENT WRONG???

    msg_surface = TTF_RenderText_Solid(msg_font, new_score.c_str(), msg_color);

    msg_texture = SDL_CreateTextureFromSurface(renderer, msg_surface);

    SDL_FreeSurface(msg_surface);

}

void Score::setScore(int x)
{
    score = x;
}

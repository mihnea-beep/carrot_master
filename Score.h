#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include "Message.h"

class Score: public Message
{
    int score = 0;

public:

    void Increment();

    void Decrement();

    void add(SDL_Renderer* renderer);

    void setScore(int x);

    void Free();

    int getScore();

    ~Score();
};



#endif // SCORE_H_INCLUDED

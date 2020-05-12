//#include "../include/Bullet.h"
#include "Bullet.h"

Bullet::Bullet()
{
    //ctor

    bool launched = false;

    bool isAlive = false;

}

bool Bullet::getLaunch()
{
    return launched;
}

void Bullet::setLaunch(bool x)
{
    launched = x;
}

Bullet::b_dir Bullet::getDir()
{
    return dir;
}

void Bullet::setDir(Bullet::b_dir bdir)
{
    dir = bdir;
}

void Bullet::setDir(string bdir)
{
    if(bdir == "right")
        dir = right;
    if(bdir == "left")
        dir = left;
    if(bdir == "up")
        dir = up;
    if(bdir == "down")
        dir = down;

   // this->dir = bdir;
}

Bullet::~Bullet()
{
    //dtor

}

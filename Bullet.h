#ifndef BULLET_H
#define BULLET_H
//#include "../Player.h"
#include "Player.h"

class Bullet: public Player
{
    enum b_dir
    {
        left,
        right,
        up,
        down,
        none

    };

    b_dir dir;

    bool launched = false;

    bool isAlive = false;


    public:

        Bullet();

        bool getLaunch();
        void setLaunch(bool);
        void setDir(string);
        void setDir(Bullet::b_dir);
        b_dir getDir();

        ~Bullet();

};

#endif // BULLET_H

#include "Player.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>

using namespace std;

Player::Player()
{
    name = "Character";
    cout<<name<<" created!"<<endl;
    texture = NULL;
    weapon = NULL;
    x = 50;
    y = 50;
    isAlive = true;

}

void Player::setLife(bool livingstatus)
{
    isAlive = livingstatus;
}

void Player::live()
{
    isAlive = true;
    randSpawn();
}

void Player::die()
{
    setPos(-100, -100);
    isAlive = false;
   // Free();

    //Free();

    deadTime = SDL_GetTicks();
}


void Player::respawn(int respawnTime)
{
    if( (SDL_GetTicks() - deadTime) > respawnTime)
        live();

}

bool Player::lifestatus()
{
    return isAlive;

}

Player::Player(SDL_Renderer* renderTarget, string FilePath, int x, int y, int framesX, int framesY, string name)
{
    this->name = name;
   // cout<<"Player name: "<<name;

    SDL_Surface* surface = IMG_Load(FilePath.c_str());
    //error checking
    if(surface == NULL)
    {
        cout<<"Image loading error! [Player]"<<endl;
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(renderTarget, surface);

        if(texture == NULL)
            cout<<"Texture creation error! [Player]"<<endl;
        else
            cout<<"Texture loaded! [Player] "<<name<<endl;
    }

    SDL_FreeSurface(surface);

    //Get the total width and the height
    SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);

    //starting position
    posRect.x = x;
    posRect.y = y;

    textureWidth = cropRect.w; // ?


    cropRect.w /= framesX; //total width divided by how many frames i
    cropRect.h /= framesY;  // have

    frameWidth = posRect.w = cropRect.w;
    frameHeight = posRect.h = cropRect.h;

    isActive = false;

    keys[0] = SDL_SCANCODE_W;
    keys[1] = SDL_SCANCODE_S;
    keys[2] = SDL_SCANCODE_A;
    keys[3] = SDL_SCANCODE_D;


    moveSpeed = 200.0f;


}

void Player::Update(float delta, const Uint8 *keyState)
{
    isActive = true;

    if(keyState[keys[0]])
    {
        posRect.y -= moveSpeed * delta;
        cropRect.y = 0;
    }

    else if(keyState[keys[1]])
    {
        posRect.y += moveSpeed * delta;
        cropRect.y = frameHeight * 2;
    }

    else if(keyState[keys[2]])
    {
        posRect.x -= moveSpeed * delta;
        cropRect.y = frameHeight;
    }

    else if(keyState[keys[3]])
    {
        posRect.x += moveSpeed * delta;
        cropRect.y = frameHeight * 3;
    }

    else

        isActive = false;

    if(isActive)
    {

        frameCounter += delta;

        if(frameCounter >= 0.1f)
        {

            frameCounter = 0;
            cropRect.x += frameWidth;

            if(cropRect.x >= textureWidth)
                cropRect.x = 0;
        }
    }

    else

    {
        frameCounter = 0;
        cropRect.x = frameWidth;
    }


}

/*void Player::Draw(SDL_Renderer* renderTarget)
{

    SDL_RenderCopy(renderTarget, texture, &cropRect, &posRect);
}*/

void Player::setImage(string filename, SDL_Renderer* ren)
{
    if(texture != NULL)
        SDL_DestroyTexture(texture);

    texture = NULL;

    SDL_Surface* psurf = IMG_Load(filename.c_str());

    texture = SDL_CreateTextureFromSurface(ren, psurf);

    SDL_FreeSurface(psurf);

}

void Player::draw(SDL_Renderer* render) // test for now
{
    SDL_Rect prect;

    prect.h = 24;
    prect.w = 24;

    SDL_RenderCopy(render, getTexture(), NULL, &prect);

}

void Player::attack(SDL_Renderer* Renderer) // here or in game?
{
    //SDL_Surface* wep_surf = IMG_Load();
    //SDL_Rect rc;
    //rc.x = 200;
    //rc.y = rc.x;
    //rc.h = rc.w = 20;
    //attacking = true;
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
    SDL_RenderDrawLine(Renderer, getX(), getY(), getX() + 100, getY());
    //SDL_RenderDrawRect(Renderer, &rc);
   // setPos(10, 10);
}

void Player::Free()
{
    if(texture != NULL)
        SDL_DestroyTexture(texture);

    texture = NULL;

}

void Player::setImage(string filename, SDL_Renderer* ren, int color_key) //color_key -> see pixel value return from SDL_MapRGB
{
    if(texture != NULL)
        SDL_DestroyTexture(texture);


    texture = NULL;

    SDL_Surface* psurf = IMG_Load(filename.c_str());

    SDL_SetColorKey(psurf, SDL_FALSE, SDL_MapRGB(psurf->format, 255, 128, 0xFF));

    texture = SDL_CreateTextureFromSurface(ren, psurf);

    SDL_FreeSurface(psurf);

}

void Player::drawPlayer(SDL_Renderer* renderer)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;

    dest.w = 20; // player tile size
    dest.h = 16; //

    SDL_RenderCopy(renderer, texture, NULL, &dest);


}

int Player::getX()
{
    return x;
}

int Player::getY()
{
    return y;
}

void Player::setX(int dx)
{
    x = dx;
}

void Player::setY(int dy)
{
    y = dy;
}

SDL_Texture* Player::getTexture() const
{
    return texture;
}

Player::Player(const string name, const string filepath, int x, int y, SDL_Renderer* renderer)
{
    this->name = name;
    this->x = x;
    this->y = y;

    SDL_Surface* psurf = IMG_Load(filepath.c_str());

    SDL_Texture* ptext = SDL_CreateTextureFromSurface(renderer, psurf);

    SDL_FreeSurface(psurf);

}

void Player::setPos(int dx, int dy)
{
    setX(dx);
    setY(dy);
}

void Player::randSpawn()
{
    setPos(rand() % 600, rand() % 400);
}

Player::~Player()
{
    if(texture != NULL)
        SDL_DestroyTexture(texture);
    //if(weapon != NULL)
      //  SDL_DestroyTexture(weapon);

    cout<<endl<<"Character deleted!";
}

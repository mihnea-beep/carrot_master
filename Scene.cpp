#include "Scene.h"
#include "GUI.h"

Scene::Scene()
{

}

void Scene::loadRes(SDL_Renderer* Renderer)
{

}

void Scene::Init(SDL_Renderer* Renderer)
{
    loadRes(Renderer);
}


void Scene::checkInput()
{

  SDL_Event ev;

  while(SDL_PollEvent(&ev))
      {
          if(ev.type == SDL_QUIT)
             {
                 cout<<"User pressed 'exit'!";
                 scene_running = false;
             }

            if(ev.type == SDL_KEYDOWN)
            {
              switch(ev.key.keysym.sym)
              {
                case SDLK_ESCAPE:

                cout<<"User pressed 'escape'!";

                scene_running = false;

                break;

                default:
                break;

              }
            }
          }

}

void Scene::update()
{

}

void Scene::render(SDL_Renderer* Renderer)
{
  SDL_SetRenderDrawColor(Renderer, 0, 80, 100, 100);
  SDL_RenderClear(Renderer);


  SDL_RenderPresent(Renderer);

}

void Scene::loop(SDL_Renderer* Renderer)
{
  while(scene_running)
  {
     //time
    checkInput();
    update();
    render(Renderer);
    //time

  }

}

void Scene::loadScene(SDL_Renderer* Renderer)
{

    loadRes(Renderer);
    loop(Renderer);
}

Scene::~Scene()
{

}

bool Scene::getRunning()
{
  return scene_running;
}

void Scene::setRunning(bool x)
{
  scene_running = x;
}

void Scene::free()
{

}

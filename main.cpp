#include <math.h> 
#include "vars.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "Instance.h"
#include "Entity.h"
#include "Paddle.h"
#include "Ball.cpp"
#include "Game.h"


const Uint8 *keys = SDL_GetKeyboardState(NULL);
int main (int argc, char* args[]) {
    Game game;

    game.init();

    SDL_Event e;
    while (!game.quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                game.quit = true;
            }
        }

        game.render();
        game.update();

        SDL_GL_SwapWindow(game.display); 
    }
    game.close();


    return 0;
}

#include <math.h>
#include <vector>
#include <memory>
#include <list>
#include <iterator>
#include "vars.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "Instance.h"
#include "Game.h"
#include "Entity.h"
#include "Ball.h"
#include "Paddle.h"



const Uint8 *keys = SDL_GetKeyboardState(NULL);
int main (int argc, char* args[]) {
    Game game;

    game.instances.insert(game.instances.begin(), new Paddle(game, 2, 0));
    game.instances.insert(game.instances.begin(),
            new Ball(game,
                ((WIDTH * SCALE) / 2) - 8,
                ((HEIGHT * SCALE) / 2) - 8)
            );

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

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


extern const int WIDTH;
extern const int HEIGHT;
extern const int SCALE;

const Uint8 *keys = SDL_GetKeyboardState(NULL);
int main (int argc, char* args[]) {
    Game game;

    game.instances.insert(game.instances.begin(), new Paddle(&game, 2, 0));
    game.instances.insert(game.instances.begin(), new Paddle(&game, (WIDTH*SCALE)-(2+16), 0));
    game.instances.insert(game.instances.begin(),
            new Ball(&game,
                ((WIDTH * SCALE) / 2) - 8,
                ((HEIGHT * SCALE) / 2) - 8)
            );

    game.init();

    SDL_Event e;
    float delta;
    int newTime;
    int oldTime = SDL_GetTicks(); 
    while (!game.quit) {
        newTime = SDL_GetTicks(); 
        delta = (float) (newTime - oldTime) / 1000;

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                game.quit = true;
            }
        }

        game.render(delta);
        game.update(delta);

        if (state[SDL_SCANCODE_X]) {
            game.instances.insert(game.instances.begin(),
                    new Ball(&game,
                        ((WIDTH * SCALE) / 2) - 8,
                        ((HEIGHT * SCALE) / 2) - 8)
                    );

        }

        SDL_GL_SwapWindow(game.display);

        SDL_Delay(1);
        oldTime = newTime; 
    }
    game.close();


    return 0;
}

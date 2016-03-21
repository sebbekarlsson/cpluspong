#pragma once
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <string>


extern const int SCALE;
extern const int WIDTH;
extern const int HEIGHT;

using namespace std;

const Uint8 *state = SDL_GetKeyboardState(NULL);

class Paddle: public Entity {
    public:

        Paddle (Game *game, float x, float y) : Entity(game, x, y) {
            this->friction = 0.5f;
            this->type = "paddle";
            this->w = 16.0f;
            this->h = 128.0f;
        }


        void draw () {
            glColor3f(0.0f, 0.0f, 0.0f);

            glPushMatrix();
            glTranslatef(this->x, this->y, 0.0f);
            glBegin(GL_QUADS);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(0.0f, this->h);
            glVertex2f(this->w, this->h);
            glVertex2f(this->w, 0.0f);
            glEnd();
            glPopMatrix();
        }


        void tick () {
            if (state[SDL_SCANCODE_UP]) {
                dy -= 2.0f;
            }
            if (state[SDL_SCANCODE_DOWN]) {
                dy += 2.0f;
                    
            }

            if (y + dy <= 0) {
                dy = 0;
                y = 0;
            }

            if ((y+h) + dy >= HEIGHT * SCALE) {
                dy = 0;
                y = (HEIGHT * SCALE)-h;
            }

            this->updatePhysics();
        }
};

#pragma once
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>


extern const int SCALE;
extern const int WIDTH;
extern const int HEIGHT;

using namespace std;

const Uint8 *state = SDL_GetKeyboardState(NULL);

class Paddle: public Entity {
    public:
        SDL_Surface * image = IMG_Load("lasse.jpg");
        SDL_Texture * texture = SDL_CreateTextureFromSurface(NULL, image);

        GLuint TextureID = 0;
        int Mode = GL_RGB;

        std::list<Instance*>::iterator iter;

        Paddle (Game *game, float x, float y) : Entity(game, x, y) {
            this->friction = 6.5f;
            this->type = "paddle";
            this->w = 42.0f;
            this->h = 156.0f;

            if(image->format->BytesPerPixel == 4) {
                Mode = GL_RGBA;
            }
        }


        void draw (float delta) {
            glColor3f(1.0f, 1.0f, 1.0f);

            glPushMatrix();
            glTranslatef(this->x, this->y, 0.0f);

            glBindTexture(GL_TEXTURE_2D, TextureID);
            glTexImage2D(GL_TEXTURE_2D, 0, Mode, image->w, image->h, 0, Mode, GL_UNSIGNED_BYTE, image->pixels);
            glBindTexture(GL_TEXTURE_2D, TextureID);
            glBegin(GL_QUADS);

            glTexCoord2f(0.0f, 0.0f);
            glVertex2f(0.0f, 0.0f);


            glTexCoord2f(0.0f, 1.0f);
            glVertex2f(0.0f, this->h);

            glTexCoord2f(1.0f, 1.0f);
            glVertex2f(this->w, this->h);


            glTexCoord2f(1.0f, 0.0f);
            glVertex2f(this->w, 0.0f);

            glEnd();
            glPopMatrix();
        }


        void tick (float delta) {
            if (state[SDL_SCANCODE_UP]) {
                dy -= 64.0f;
            }
            if (state[SDL_SCANCODE_DOWN]) {
                dy += 64.0f;
            }

            if (y + (dy*delta) <= 0) {
                dy = 0;
                y = 0;
            }

            if ((y+h) + (dy*delta) >= HEIGHT * SCALE) {
                dy = 0;
                y = (HEIGHT * SCALE)-h;
            }

            this->updatePhysics(delta);
        }
};

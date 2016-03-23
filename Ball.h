#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>


using namespace std;
extern const int SCALE;
extern const int WIDTH;
extern const int HEIGHT;

class Game;
class Ball: public Entity {
    public:
        float w = 42;
        float h = 42;
        float r = 0.0f;
        SDL_Surface * image = IMG_Load("b1.png");
        SDL_Texture * texture = SDL_CreateTextureFromSurface(NULL, image);

        GLuint TextureID = 0;
        int Mode = GL_RGB;

        std::list<Instance*>::iterator iter;


        Ball (Game *game, float x, float y) : Entity(game, x, y) {
            this->friction = 0.0001f;
            this->type = "ball";

            srand(time(NULL)); 
            float randNum = rand()%(360-0 + 1) + 0;
            this->addForce(randNum, 200.0f);

            if(image->format->BytesPerPixel == 4) {
                Mode = GL_RGBA;
            }
        }


        void draw (float delta) {
            glColor3f(1.0f, 1.0f, 1.0f);
            
            glPushMatrix();
            
            glTranslatef(this->x, this->y, 0.0f);
            glRotatef(r, 0.0f, 0.0f, 1.0f);

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
            Instance *instance;
            for (iter = this->game->instances.begin() ; iter != this->game->instances.end(); iter++) {
                instance = &**iter;

                if (instance == this) {
                    continue;
                }

                float inst_x = instance->x;
                float inst_y = instance->y;
                float inst_w = instance->w;
                float inst_h = instance->h;

                if (y + (dy * delta) <= 0) {
                    bounce(2.0f, delta);
                }
                if ((y+h) + (dy * delta) >= HEIGHT * SCALE) {
                    bounce(2.0f, delta);
                }

                if (x + (dx * delta) <= 0) {
                    bounce(2.0f, delta);
                }
                if ((x+w) + (dx * delta) >= WIDTH * SCALE) {
                    bounce(2.0f, delta);
                }

                if ((y+h) + (dy * delta) >= inst_y && y+(dy * delta) <= inst_y+inst_h) {
                    if ((x+w)+(dx * delta) >= inst_x && x+(dx * delta) <= inst_x+inst_w) {
                        bounce(60.0f, delta);

                        if (instance->type != "paddle") {
                            instance->bounce(2.0f, delta, true);
                        }
                    }
                }

            }


            if (
                    x > (WIDTH * SCALE) + 32 ||
                    x < -32 ||
                    y > (HEIGHT * SCALE) + 32 ||
                    y < -32
               ) {
                x = ((WIDTH * SCALE) / 2) - 8;
                y = ((HEIGHT * SCALE) / 2) - 8;
                srand(time(NULL)); 
                float randNum = rand()%(360-0 + 1) + 0;
                this->addForce(randNum, 200.0f);

            }

            r += 0.1f;

            this->updatePhysics(delta);
        }
};

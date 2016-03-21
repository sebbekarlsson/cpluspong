#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <string>

using namespace std;
extern const int SCALE;
extern const int WIDTH;
extern const int HEIGHT;


class Game;
class Ball: public Entity {
    public:
        float w = 16;
        float h = 16;

        std::list<Instance*>::iterator iter;


        Ball (Game *game, float x, float y) : Entity(game, x, y) {
            this->friction = 0.0001f;
            this->type = "ball";

            srand(time(NULL)); 
            float randNum = rand()%(360-0 + 1) + 0;
            this->addForce(0.0f, 12.0f);
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
            Instance *instance;
            for (iter = this->game->instances.begin() ; iter != this->game->instances.end(); iter++) {
                instance = &**iter;

                if (instance->type == "ball") {
                    continue;
                }

                float inst_x = instance->x;
                float inst_y = instance->y;
                float inst_w = instance->w;
                float inst_h = instance->h;

                if (y + (dy) <= 0) {
                    bounce(3.0f);
                }
                if ((y+h) + (dy) >= HEIGHT * SCALE) {
                    bounce(3.0f);
                }

                if (x + (dx) <= 0) {
                    bounce(3.0f);
                }
                if ((x+w) + (dx) >= WIDTH * SCALE) {
                    bounce(3.0f);
                }

                if ((y+h) + (dy) >= inst_y && y+(dy) <= inst_y+inst_h) {
                    if ((x+w)+(dx) >= inst_x && x+(dx) <= inst_x+inst_w) {
                        bounce(5.2f);
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

            this->updatePhysics();
        }


        void bounce (float m) {
            float speed = ((px - x) + (py - y) / 2);
            if (speed >= 1.5f) {  speed = 1.5f;  }

            float dir = atan2(py - y, px - x) * 180 / M_PI;
            cout << dir << endl;

            dx = 0;
            dy = 0;

            this->addForce(-dir , m);
        }
};

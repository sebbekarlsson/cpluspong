#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL.h>

extern const int SCALE;
extern const int WIDTH;
extern const int HEIGHT;


class Game;
class Ball: public Entity {
    public:
        float w = 16;
        float h = 16;


        Ball (Game& game, float x, float y) : Entity(game, x, y) {
            this->friction = 0.1f;
            
            srand(time(NULL)); 
            float randNum = rand()%(360-0 + 1) + 0;
            this->addForce(randNum, 12.0f);
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
            this->updatePhysics();
        }
};

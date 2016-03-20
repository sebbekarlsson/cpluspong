#pragma once
#include "Instance.h"


class Entity: public Instance {
    public:
        float dx = 0.0f;
        float dy = 0.0f;
        float friction = 0.1f;
        Game game;

        Entity (Game& game, float x, float y) : Instance(x, y) {
            this->game = game;
        }


        void updatePhysics () {
            if(dx > 0){
                if(dx - friction < 0){
                    dx = 0;
                }else{
                    dx -= friction;
                }
            }
            if(dx < 0){
                if(dx + friction > 0){
                    dx = 0;
                }else{
                    dx += friction;
                }
            }

            if(dy > 0){
                if(dy - friction < 0){
                    dy = 0;
                }else{
                    dy -= friction;
                }
            }
            if(dy < 0){
                if(dy + friction > 0){
                    dy = 0;
                }else{
                    dy += friction;
                }
            }

            x += dx;
            y += dy;
        }


        void addForce (float direction, float force) {
            float radians = direction * M_PI / 180.0; 
            dx += (float) (cos(radians) * force);
	    dy += (float) (sin(radians) * force);
        }
};

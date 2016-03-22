#pragma once
#include "Instance.h"
#include <iostream>

using namespace std;


class Entity: public Instance {
    public:
        Game *game;

        Entity (Game *game, float x, float y) : Instance(x, y) {
            this->game = game;
        }


        void updatePhysics (float delta) {
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
            
            px = x - (dx*delta);
            py = y - (dy*delta);
            x += dx * delta;
            y += dy * delta;
        }

};

#pragma once
#include <iostream>
#include <typeinfo>
#include <string>
#include <iostream>

using namespace std;
class Instance {
    public:
        float x = 0;
        float y = 0;
        float w = 0;
        float h = 0;
        float px = 0;
        float py = 0;
        float dx = 0.0f;
        float dy = 0.0f;
        float friction = 0.1f;
        string type = "instance";



        Instance (float x, float y) {
            this->x = x;
            this->y = y;
        }


        virtual void tick(float delta) = 0;
        virtual void draw(float delta) = 0;


        void addForce (float direction, float force) {
            float radians = direction * M_PI / 180.0; 
            dx += (float) (cos(radians) * force);
	    dy += (float) (sin(radians) * force);
        }


        void bounce (float m, float delta, bool revert=false) {
            float distance = sqrt((x-(x-dx * delta))*(x-(x-dx * delta)) + (y-(y-dy * delta))*(y-(y-dy * delta)));
            float speed = distance/delta;
            float dir = atan2(py - y, px - x) * 180 / M_PI;

            dx = 0;
            dy = 0;

            if (revert == true) {
                dir = -dir;
            }

            this->addForce(dir , speed+m);
        }
};

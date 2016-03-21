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


        virtual void tick() = 0;
        virtual void draw() = 0;
};

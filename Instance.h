#pragma once
#include <iostream>


class Instance {
    public:
        float x = 0;
        float y = 0;



        Instance (float x, float y) {
            this->x = x;
            this->y = y;
        }


        virtual void tick() = 0;
        virtual void draw() = 0;
};

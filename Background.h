#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <stdlib.h>

using namespace sf;
using namespace std;

class Background {
    public:
    Sprite shape;

    // constructor 
    Background(Texture *texture, Vector2f position) {
        shape.setTexture(*texture);
        shape.setPosition(position);
        shape.setScale(4,4);
    }

    // move background
    void moveBackground() {
        shape.move(0,1);
        if (shape.getPosition().y > 999) {
            shape.setPosition(0,-1000);
        }
    }

    void setTex(Texture *texture) {
        shape.setTexture(*texture);
    }
};


#endif
#ifndef EFFECT_H
#define EFFECT_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <stdlib.h>

using namespace sf;
using namespace std;

class Effect {
    public:
    Sprite shape;
    Texture *tex1;

    // constructor for effect
    Effect(Texture *texture0, Texture *texture1, Vector2f position) {
        shape.setTexture(*texture0);
        shape.setScale(4,4);
        shape.setPosition(position);
        tex1 = texture1;
    }

    // animation
    // animates by changing texture every x frames
    // when animation is done, returns true so we know when to delete it
    int frame = 0;
    bool animateEffect() {
        if (frame == 10) {
            shape.setTexture(*tex1);
        } else if (frame == 15) {
            return true;
        }
        frame++;
        return false;
    }

    Effect (){}
    ~Effect () {}
};

#endif
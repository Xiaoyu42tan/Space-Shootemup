#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <stdlib.h>

using namespace sf;
using namespace std;


class Projectile {
    public:
    Sprite shape;
    int projSpeed;
    int dmg;

    // constructor for projectile
    Projectile(Texture *texture, Vector2f position, int projSpeed) {
        shape.setTexture(*texture);
        shape.setPosition(position);
        shape.setScale(4,4);
        this->projSpeed = projSpeed;
        dmg = 30;
    }

    Projectile() {}

    ~Projectile(){}
};


#endif
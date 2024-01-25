#ifndef HITBOX_H
#define HITBOX_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <stdlib.h>

using namespace sf;
using namespace std;


class HitBox {
    public:
    RectangleShape shape;
    FloatRect box;

    // debug hitbox, standard constructor
    // standard hitbox should not appear on screen
    HitBox(){
        shape.setSize(Vector2f(0,0));
        shape.setFillColor(Color::Red);
        box = shape.getGlobalBounds();
    }
    
    ~HitBox(){}
    
    // follow the target
    void Follow(Vector2f position) {
        shape.setPosition(position);
    }

    // check for projectile collision
    bool CheckHit(Vector2f point) {
        if (box.contains(point)) {
            return true;
        }
        return false;
    }

    // check for entity collision
    bool CheckCollision(FloatRect box) {
        if (this->box.intersects(box)) {
            return true;
        }
        return false;
    }

    // update hitbox bounds
    void UpdateHitbox() {
        box = shape.getGlobalBounds();
    }

};


#endif
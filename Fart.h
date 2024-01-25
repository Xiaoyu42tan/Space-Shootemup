#ifndef FART_H
#define FART_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "Ship.h"
#include "Projectile.h"
#include "Entity.h"
#include "HitBox.h"

using namespace sf;
using namespace std;

class Fart: public Ship {
    public:
    // initalise fart stats, and hitbox
    Fart(Texture* tex, Texture *texDmg, Vector2f position, Vector2f origin):Ship(tex,texDmg,position,origin){
        hp = 300;
        maxspeed = 3;
        boundaryY = rand() % 400 + 50;
        distanceX = rand() % 40 + 1;
        worth = 1;
        initHitBox();
    }
    Fart() {}

    // every fart has its own hitbox
    HitBox hitbox;

    // init hitbox size, etc
    void initHitBox() {
        hitbox.shape.setSize(Vector2f(4*13,4*16));
        hitbox.shape.setFillColor(Color::Transparent);
        hitbox.box = shape.getGlobalBounds();
        hitbox.shape.setPosition(shape.getPosition().x+4*5,shape.getPosition().y+4*6);
    }

    // fart is not an abstract class, takeDamage is defined
    void takeDamage(int dmg) {
        dmgFrame = 0;
        hp = hp - dmg;
    }

    // movement mechanics
    // direction of movement is defined by a 2d vector
    int boundaryY;
    int distanceX;
    void movement(Vector2f playerPos) {
        // movement randomiser
        int negativeRandom = rand() % 2 + 1;
        distanceX = rand() % 100 + 1;
        if (negativeRandom == 1) {
            distanceX = -distanceX;
        }

        // movement rules, always move towards player until a certain y point
        if (playerPos.x-shape.getPosition().x > distanceX) {
            direction.x += .2;
        } else {
            direction.x -= .2;
        }
        if (playerPos.y-shape.getPosition().y > 0) {
            direction.y += .2;
        } else {
            direction.y -= .2;
        }
        if (shape.getPosition().y > boundaryY && shape.getPosition().y < boundaryY+50) {
            direction.y = 0;
        }
        // max speed
        if (direction.x > maxspeed) {
            direction.x = maxspeed;
        } else if (direction.x < -maxspeed) {
            direction.x = -maxspeed;
        }
        if (direction.y > maxspeed) {
            direction.y = maxspeed;
        } else if (direction.y < -maxspeed) {
            direction.y = -maxspeed;
        }
        // move 
        shape.move(direction);
    }
    
};

#endif
#ifndef ASTEROID_H
#define ASTEROID_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "Entity.h"
#include "HitBox.h"

using namespace sf;
using namespace std;

class Asteroid: public Entity {
    public:

    // takedamage is defined, asteroid is not abstract
    void takeDamage(int dmg) {
        dmgFrame = 0;
        hp = hp - dmg;
    }

    // init hitbox
    HitBox hitbox;
    // asteroid constructor
    Asteroid(Texture* texture, Texture* texDmg, Vector2f position, Vector2f origin):Entity(texture,texDmg,position,origin){
        // init some stats
        hp = 300;
        initHitBox();
        int x = rand() % 7 + 0;
        int speed = rand() % 10 + 1;
        rotate = rand() % 10 + 2;        
        direction.x = speed*(100*x - shape.getPosition().x)/1000; 
        direction.y = speed*(1000 - shape.getPosition().y)/1000;
    };
    Asteroid(){}

    // init hitbox
    void initHitBox() {
        hitbox.shape.setSize(Vector2f(4*16,4*17));
        hitbox.shape.setFillColor(Color::White);
        hitbox.box = shape.getGlobalBounds();
        hitbox.shape.setPosition(shape.getPosition().x-4*12+4*4,shape.getPosition().y-4*11+4*3);
    }
    
    // movement mechanics
    int rotate;
    void movement() {
        shape.rotate(rotate);
        shape.move(direction);
    }

    // animate damage
    bool animateDmg() {
        if (dmgFrame != 5) {
            shapeDmg.setPosition(Vector2f(shape.getPosition().x-4*12,shape.getPosition().y-4*11));
            dmgFrame++;
            return true;
        }
        return false;
    }

    // collision mechanics
    bool collisionWindow() {
        if (shape.getPosition().y > 1200) {
            return true;
        }
        return false;
    }
};

#endif
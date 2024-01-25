#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <stdlib.h>

using namespace sf;
using namespace std;


class Entity {
    public:
    Sprite shape;
    int hp;
    bool dead = false;
    Vector2f direction = Vector2f(0,0);
    Sprite shapeDmg;

    // check for death
    void isDead() {
        if (hp < 1) {
            dead = true;
        }
    }

    // animate death
    // animates by changing texture every x frames
    // when animation is done, returns true so we know when to delete it
    int deadFrame = 0;
    bool animateDeath(Texture *deadTex1, Texture *deadTex2) {
        if (dead == false) {
            return false;
        }
        direction = Vector2f(0,0);
        if (deadFrame < 10) {
            shape.setTexture(*deadTex1);
        } else if (deadFrame < 20) {
            shape.setTexture(*deadTex2);
        } else if (deadFrame == 20) {
            return true;
        }
        deadFrame++;
        return false;
    }

    // animate dmg
    int dmgFrame = 5;
    bool animateDmg() {
        if (dmgFrame != 5) {
            shapeDmg.setPosition(shape.getPosition());
            dmgFrame++;
            return true;
        }
        return false;
    }

    // entity constructor
    Entity(Texture* tex, Texture *texDmg, Vector2f position, Vector2f origin) {
        shape.setTexture(*tex);
        shape.setScale(4,4);
        shapeDmg.setTexture(*texDmg);
        shapeDmg.setScale(4,4);
        shape.setOrigin(origin);
        shape.setPosition(position);
    }

    Entity(){}

    // entity is abstract class, all entities can take damage
    virtual void takeDamage(int dmg) = 0;

};


#endif
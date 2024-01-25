#ifndef SHIP_H
#define SHIP_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "Entity.h"
#include "Projectile.h"

using namespace sf;
using namespace std;

class Ship: public Entity {
    public:

    // how much score the ship is worth when killed
    int worth;

    // constructor, inherits from entity constructor
    // ship is abstract class
    Ship(Texture* tex, Texture* texDmg, Vector2f position, Vector2f origin):Entity(tex,texDmg,position,origin){}
    Ship() {}

    // movement stats
    float maxspeed = 10;
    float friction = 0.1;

    // ship animation
    // animates by changing texture every x frames
    int frame = 0;
    void animateShip(Texture* shipTex0,Texture* shipTex1,Texture* shipTex2,Texture* shipTex3) {
        if (frame <= 12) {
            shape.setTexture(*shipTex0);
        } else if (frame <= 24) {
            shape.setTexture(*shipTex1);
        } else if (frame <= 36) {
            shape.setTexture(*shipTex2);
        } else if (frame <= 48) {
            shape.setTexture(*shipTex3);
        } else if (frame > 48) {
            frame = 0;
        }
        frame++;
    }

    // window collision mechanic
    void collisionWindow() {
        if (shape.getPosition().x+4*11 < 0) {
            shape.setPosition(800-4*11,shape.getPosition().y);
        } else if (shape.getPosition().x+4*11 > 800) {
            shape.setPosition(0-4*11,shape.getPosition().y);
        }
    }

    // projectiles, every ship has own vector of projectiles
    vector<Projectile> projectiles;

    // shooting stats
    int firerate = 30;
    int weaponCooldown = firerate;
    int shootFrame = 0;
    // shooting
    void shooting(Texture* projTex, Texture* fireTex0, Texture* fireTex1, int projSpeed) {
        // check if ship can shoot
        if (weaponCooldown < firerate) {
            weaponCooldown++;
        }
        // only shoot if onscreen, and is able to shoot
        if (weaponCooldown == firerate && shape.getPosition().y > 0) {
            projectiles.push_back(Projectile(projTex,Vector2f(shape.getPosition().x+4*10,shape.getPosition().y+4*17),projSpeed));
            weaponCooldown = 0;
            shootFrame = 0;
        }

        // animate ship fire effect
        if (shootFrame < 4) {
            shape.setTexture(*fireTex0);
            // cout << shootFrame << endl;
        } else if (shootFrame < 7) {
            shape.setTexture(*fireTex1);
            // cout << shootFrame << endl;
        }
        if (shootFrame < 8) {
            shootFrame++;
        }

        // move and delete projectiles
        for (size_t i = 0;i < projectiles.size();i++) {
            // move projectile 
            projectiles[i].shape.move(0,projectiles[i].projSpeed);
            // delete projectile
            if (projectiles[i].shape.getPosition().y > 1000) {
                projectiles.erase(projectiles.begin() + i);
            }
        }
    }

};

#endif
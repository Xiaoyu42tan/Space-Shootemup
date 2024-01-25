#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "Ship.h"
#include "Entity.h"
#include "Projectile.h"
#include "HitBox.h"

using namespace sf;
using namespace std;

class Player: public Ship {
    public:

    // player constructor
    Player(Texture* tex, Texture* texDmg, Vector2f position, Vector2f origin):Ship(tex,texDmg,position,origin) {
        hp = 100;
        initHitBox();
    }
    
    // takeDamage is defined, player is not abstract class
    void takeDamage(int dmg) {
        dmgFrame = 0;
        hp = hp - dmg;
    }

    // initalise hitbox
    HitBox hitbox;
    void initHitBox() {
        hitbox.shape.setSize(Vector2f(4*13,4*8));
        hitbox.shape.setFillColor(Color::Transparent);
        hitbox.box = shape.getGlobalBounds();
        hitbox.shape.setPosition(shape.getPosition().x+4*5,shape.getPosition().y+4*5);
    }

    bool movingx = false;
    bool movingy = false;
    // player movement
    void movement() {
        // keyboard inputs
        movingx = false;
        movingy = false;
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            direction.x -= 1;
            movingx = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            direction.x += 1;
            movingx = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::A)) {
            movingx = false;
        }
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            direction.y -= 1;
            movingy = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            direction.y += 1;
            movingy = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::S)) {
            movingy = false;
        }
        // friction
        if (movingx == false && direction.x > 0) {
            direction.x -= friction;
        }
        if (movingy == false && direction.y > 0) {
            direction.y -= friction;
        }
        if (movingx == false && direction.x < 0) {
            direction.x += friction;
        }
        if (movingy == false && direction.y < 0) {
            direction.y += friction;
        }
        // friction floating point bug fix
        if (direction.x > -0.1 && direction.x < 0.1) {
            direction.x = 0;
        }
        if (direction.y > -0.1 && direction.y < 0.1) {
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
        shape.move(direction.x,direction.y);
    }
    // window collision
    void collisionWindow() {
        // can jump from left to right of screen, but is restricted from jumping top to bottom
        if (shape.getPosition().x+4*11 < 0) {
            shape.setPosition(800-4*11,shape.getPosition().y);
        } else if (shape.getPosition().x+4*11 > 800) {
            shape.setPosition(0-4*11,shape.getPosition().y);
        } else if (shape.getPosition().y+4*9 < 0) {
            shape.setPosition(shape.getPosition().x,0-4*9);
        } else if (shape.getPosition().y+4*9 > 1000) {
            shape.setPosition(shape.getPosition().x,1000-4*9);
        }
    }
    // entity collision
    void bounce(Vector2f object) {
        // bounce off of entity and take damage
        Vector2f dir = Vector2f((shape.getPosition().x-object.x)/2,(shape.getPosition().y - object.y)/2);
        direction = dir;
        takeDamage(20);
    }

    // player shooting
    // polymorphism: overrides parent function because player shooting mechanics differ from enemies
    void shooting(Texture* projTex, Texture* fireTex0, Texture* fireTex1, int projSpeed) {
        // check if ship can shoot
        if (weaponCooldown < firerate) {
            weaponCooldown++;
        }
        if (Keyboard::isKeyPressed(Keyboard::Space) && weaponCooldown == firerate) {
            projectiles.push_back(Projectile(projTex,Vector2f(shape.getPosition().x+4*7,shape.getPosition().y),projSpeed));
            projectiles.push_back(Projectile(projTex,Vector2f(shape.getPosition().x+4*15,shape.getPosition().y),projSpeed));
            weaponCooldown = 0;
            shootFrame = 0;
        }

        // animate ship fire effect
        if (shootFrame < 2) {
            shape.setTexture(*fireTex0);
        } else if (shootFrame < 5) {
            shape.setTexture(*fireTex1);
        }
        if (shootFrame < 7) {
            shootFrame++;
        }

        for (size_t i = 0;i < projectiles.size();i++) {
            // move projectile 
            projectiles[i].shape.move(0,-projectiles[i].projSpeed);
            // delete projectile
            if (projectiles[i].shape.getPosition().y < 0) {
                projectiles.erase(projectiles.begin() + i);
            }
        }
    }

    // score system
    int score = 0;
    void addScore(int points) {
        score = score + points;
    }
};

#endif
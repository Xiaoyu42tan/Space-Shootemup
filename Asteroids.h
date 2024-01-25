#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "Asteroid.h"

using namespace sf;
using namespace std;

class Asteroids {
    public:
    
    // array of asteroids
    Asteroid* asteroids;
    // track current asteroid count
    int asteroidCount = 0;
    
    // same as enemies add and remove functions
    void addAsteroid(Asteroid asteroid) {
        Asteroid* temp = new Asteroid[asteroidCount+1];
        temp[asteroidCount] = asteroid;
        for (int i = 0;i < asteroidCount;i++) {
            temp[i] = asteroids[i];
        }
        if (asteroidCount > 0) {delete[] asteroids;}
        asteroids = temp;
        asteroidCount++;
        return;
    }
    void rmAsteroid(int number) {
        Asteroid* temp = new Asteroid[asteroidCount-1];
        int j = 0;
        for (int i = 0;i < asteroidCount;i++) {
            if (i != number) {
                temp[j] = asteroids[i];
                j++;
            }
        }
        if (asteroidCount > 0) {delete[] asteroids;}
        asteroids = temp;
        asteroidCount--;
        return;
    }

    Asteroids(){}
};

#endif
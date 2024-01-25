#ifndef ENEMIES_H
#define ENEMIES_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "Fart.h"

using namespace sf;
using namespace std;

class Enemies {
    public:

    // initialise array of enemies
    Fart* farts;
    // tracks current number of enemies
    int fartCount = 0;
    
    // add a fart
    // dynamic allocation, allocates extra memory for fart whenever fart is added
    void addFart(Fart fart) {
        Fart* temp = new Fart[fartCount+1];
        temp[fartCount] = fart;
        for (int i = 0;i < fartCount;i++) {
            temp[i] = farts[i];
        }
        if (fartCount > 0) {delete[] farts;}
        farts = temp;
        fartCount++;
        return;
    }
    // remove a fart
    // dynamic allocation, decrease allocated memory when fart is removed
    void rmFart(int number) {
        Fart* temp = new Fart[fartCount-1];
        int j = 0;
        for (int i = 0;i < fartCount;i++) {
            if (i != number) {
                temp[j] = farts[i];
                j++;
            }
        }
        if (fartCount > 0) {delete[] farts;}
        farts = temp;
        fartCount--;
        return;
    }
    // fart array can only ever fit the amount of farts current in it

    // default constructor
    Enemies(){}

};

#endif
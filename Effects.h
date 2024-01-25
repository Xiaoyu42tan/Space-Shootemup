#ifndef EFFECTS_H
#define EFFECTS_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include "Effect.h"

using namespace sf;
using namespace std;

class Effects {
    public:
    vector<Effect> effects;

    // add effect to effect vector
    void AddEffect(Texture *texture0, Texture *texture1, Vector2f position) {
        effects.push_back(Effect(texture0,texture1,position));
    }

    // animates all effects, and deletes them when done
    void animateEffects() {
        for (size_t i = 0;i < effects.size();i++) {
            if (effects[i].animateEffect() == true) {
                effects.erase(effects.begin() + i);
                // cout << "Effect was deleted" << endl;
            }
        }
    }

    Effects(){}
};


#endif
#ifndef NOTAFUNCTION_H
#define NOTAFUNCTION_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <stdlib.h>

using namespace sf;
using namespace std;

class NotAFunction {
    public:
    NotAFunction(){}
    View a_function(View view, int windowWidth, int windowHeight) {
        // Compares the aspect ratio of the window to the aspect ratio of the view,
        // and sets the view's viewport accordingly in order to archieve a letterbox effect.
        // A new view (with a new viewport set) is returned.

        float windowRatio = windowWidth / (float) windowHeight;
        float viewRatio = view.getSize().x / (float) view.getSize().y;
        float sizeX = 1;
        float sizeY = 1;
        float posX = 0;
        float posY = 0;

        bool horizontalSpacing = true;
        if (windowRatio < viewRatio)
            horizontalSpacing = false;

        // If horizontalSpacing is true, the black bars will appear on the left and right side.
        // Otherwise, the black bars will appear on the top and bottom.

        if (horizontalSpacing) {
            sizeX = viewRatio / windowRatio;
            posX = (1 - sizeX) / 2.f;
        }

        else {
            sizeY = windowRatio / viewRatio;
            posY = (1 - sizeY) / 2.f;
        }

        view.setViewport( FloatRect(posX, posY, sizeX, sizeY) );

        return view;
    }
};

#endif
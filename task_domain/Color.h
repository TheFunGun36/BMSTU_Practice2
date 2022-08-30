#pragma once
#include "Real.h"

struct Color {
    int r;
    int g;
    int b;
    int alpha;

    Color();
    Color(int r, int g, int b, int alpha = 0);
    bool isValid();
    
    static Color blend(Color a, Color b, real coef);
};


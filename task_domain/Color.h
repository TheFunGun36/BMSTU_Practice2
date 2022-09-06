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

    Color& operator+=(const Color& other);
    Color operator+(const Color& other);
    Color& operator*=(real v);
    Color operator*(real v);
    static Color blend(Color a, Color b, real coef);
};


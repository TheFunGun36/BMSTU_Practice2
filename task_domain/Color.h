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

    Color& operator+=(const Color& other) noexcept;
    Color operator+(const Color& other) const noexcept;
    Color& operator*=(real v) noexcept;
    Color operator*(real v) const noexcept;
    bool operator==(const Color& other) const noexcept;
;
    static Color blend(Color a, Color b, real coef) noexcept;
    static Color intensity(Color color, real intencity) noexcept;
    Color& normalize_up();
};


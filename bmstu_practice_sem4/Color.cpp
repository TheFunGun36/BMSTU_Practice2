#include "Color.h"

Color::Color()
    : r(0), g(0), b(0), alpha(0) {}

Color::Color(int r, int g, int b, int alpha)
    : r(r), g(g), b(b), alpha(alpha) {}


static inline bool inRange(int x) {
    return x >= 0 && x <= 255;
}

bool Color::isValid() {
    return inRange(r) && inRange(g) && inRange(b) && inRange(alpha);
}

Color Color::blend(Color a, Color b, real coef) {
    const real rev_coef = 1 - coef;
    return Color(
        a.r * coef + b.r * rev_coef,
        a.g * coef + b.g * rev_coef,
        a.b * coef + b.b * rev_coef,
        a.alpha * coef + b.alpha * rev_coef
        );
}

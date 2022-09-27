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

Color& Color::operator+=(const Color& other) {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
}

Color Color::operator+(const Color& other) {
    return Color(r + other.r, g + other.g, b + other.b);
}

Color& Color::operator*=(real v) {
    r *= v;
    g *= v;
    b *= v;
    return *this;
}
Color Color::operator*(real v) {
    return Color(r * v, g * v, b * v);
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

Color Color::intensity(Color color, real intencity) {
    return (color * real_max(intencity, 0.2)).normalize_up();

}

Color& Color::normalize_up() {
    r = real_min(255, r);
    g = real_min(255, g);
    b = real_min(255, b);
    return *this;
}

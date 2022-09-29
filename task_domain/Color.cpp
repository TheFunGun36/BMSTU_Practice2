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

Color& Color::operator+=(const Color& other) noexcept {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
}

Color Color::operator+(const Color& other) const noexcept {
    return Color(r + other.r, g + other.g, b + other.b);
}

Color& Color::operator*=(real v) noexcept {
    r *= v;
    g *= v;
    b *= v;
    return *this;
}
Color Color::operator*(real v) const noexcept{
    return Color(r * v, g * v, b * v);
}

bool Color::operator==(const Color& o) const noexcept {
    return r == o.r && g == o.g && b == o.b && alpha == o.alpha;
}

static bool equal(const Color& a, const Color& b, real tolerance = 0.) {
    return real_eq(a.r, b.r, tolerance)
        && real_eq(a.g, b.g, tolerance)
        && real_eq(a.b, b.b, tolerance)
        && real_eq(a.alpha, b.alpha, tolerance);
}

Color Color::blend(Color a, Color b, real coef) noexcept {
    const real rev_coef = 1 - coef;
    return Color(
        a.r * coef + b.r * rev_coef,
        a.g * coef + b.g * rev_coef,
        a.b * coef + b.b * rev_coef,
        a.alpha * coef + b.alpha * rev_coef);
}

Color Color::intensity(Color color, real intencity) noexcept {
    return (color * real_max(intencity, 0.2)).normalize_up();

}

Color& Color::normalize_up() {
    r = real_min(255, r);
    g = real_min(255, g);
    b = real_min(255, b);
    return *this;
}

#include <iostream>
#include <cmath>
#include "Vec2.h"

Vec2::Vec2() : y(0.0), r(0.0) {
    // nop
}

Vec2::Vec2(const Vec2 &other) : y(other.y), r(other.r) {
    // nop
}

Vec2::Vec2(float y, float r) : y(y), r(r) {
    // nop
}

Vec2& Vec2::operator=(const Vec2 &rhs) {
    if(&rhs == this) {
        return *this;
    }

    y = rhs.y;
    r = rhs.r;
    return *this;
}

Vec2& Vec2::operator+=(const Vec2 &rhs) {
    y += rhs.y;
    r += rhs.r;
    return *this;
}

Vec2 Vec2::operator+(const Vec2 &rhs) const {
    return {
            y + rhs.y,
            r + rhs.r
    };
}

Vec2 Vec2::operator-(const Vec2 &rhs) const {
    return {
            y - rhs.y,
            r - rhs.r
    };
}

Vec2 Vec2::operator*(const float scalar) const {
    return {
            y * scalar,
            r * scalar
    };
}

Vec2 Vec2::operator/(const float scalar) const {
    return {
            y / scalar,
            r / scalar
    };
}

float Vec2::magnitude() const {
    return std::sqrt(
            std::pow(y, 2) +
            std::pow(r, 2)
    );
}

Vec2 Vec2::normal() const {
    float factor = 1.0 / magnitude();
    return (*this) * factor;
}

std::ostream &operator<<(std::ostream &os, Vec2 const &v) {
    os << "{"
       << v.y << ", "
       << v.r
       << "}";
    return os;
}

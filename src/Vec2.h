#pragma once

struct Vec2 {
    float y;
    float r;

    Vec2();
    Vec2(const Vec2 &other);
    Vec2(float y, float r);

    Vec2& operator=(const Vec2 &rhs);
    Vec2& operator+=(const Vec2 &rhs);
    Vec2 operator+(const Vec2 &rhs) const;
    Vec2 operator-(const Vec2 &rhs) const;
    Vec2 operator*(const float scalar) const;
    Vec2 operator/(const float scalar) const;

    float magnitude() const;
    Vec2 normal() const;
};

std::ostream &operator<<(std::ostream &os, Vec2 const &v);

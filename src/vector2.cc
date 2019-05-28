#include "vector2.h"

namespace Ann
{

Vector2::Vector2() : x(0), y(0) { }
Vector2::~Vector2() { }

Vector2::Vector2(int x, int y) {
    this->x = x;
    this->y = y;
}

bool Vector2::operator==(const Vector2& vec2) {
    return this->x == vec2.x && this->y == vec2.y;
}

bool Vector2::operator!=(const Vector2& vec2) {
    return this->x != vec2.x || this->y != vec2.y;
}

Vector2 Vector2::operator+(const Vector2& vec2) const {
    return Vector2(this->x + vec2.x, this->y + vec2.y);
}

Vector2 Vector2::operator-(const Vector2& vec2) const {
    return Vector2(this->x - vec2.x, this->y - vec2.y);
}

Vector2 Vector2::operator*(int scalar) const {
    return Vector2(this->x * scalar, this->y * scalar);
}

Vector2 Vector2::operator/(int scalar) const {
    return Vector2(this->x / scalar, this->y / scalar);
}

} // namespace Ann

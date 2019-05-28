#ifndef _SOLVER_VECTOR2
#define _SOLVER_VECTOR2

namespace ann
{
struct Vector2
{
    int x, y;

    Vector2();
    Vector2(int x, int y);
    ~Vector2();

    Vector2 operator+(const Vector2& vec2) const;
    Vector2 operator-(const Vector2& vec2) const;
    Vector2 operator*(int scalar) const;
    Vector2 operator/(int scalar) const;
    bool operator==(const Vector2& vec2);
    bool operator!=(const Vector2& vec2);
};
}

#endif

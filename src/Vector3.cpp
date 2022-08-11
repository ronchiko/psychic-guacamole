#include "Vector3.hpp"

Vector3::~Vector3()
{
    delete this;
}

Vector3 &Vector3::operator+=(Vector3 const &v)
{
    x += v.x;
    y += v.y;
    return *this;
}

Vector3 &Vector3::operator-=(Vector3 const &v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector3 &Vector3::operator*=(float const &f)
{
    x *= f;
    y *= f;
    return *this;
}
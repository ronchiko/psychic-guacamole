#pragma once

class Vector3 {
public:
    float x, y;

    inline Vector3(float a, float b) noexcept {x = a; y = b;};
    ~Vector3();

    Vector3& operator += (Vector3 const& v);
    Vector3& operator -= (Vector3 const& v);
    Vector3& operator *= (float const& f);
    //Vector3 operator + (Vector3 v1, Vector3 const& v2);
    float Angle();
};
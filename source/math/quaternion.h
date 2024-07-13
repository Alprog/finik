
#pragma once

class Quaternion
{
public:
    static const Quaternion Identity;

    Quaternion(float x = 0, float y = 0, float z = 0, float w = 1);

    static Quaternion yawPitchRoll(float yaw, float pitch, float roll);

    float x, y, z, w;
};

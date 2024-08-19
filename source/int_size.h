#pragma once

struct IntSize
{
public:
    int width;
    int height;

    friend bool operator==(const IntSize& a, const IntSize& b) = default;
    friend bool operator!=(const IntSize& a, const IntSize& b) = default;
};
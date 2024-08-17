#pragma once

struct Texel
{
    static const Texel Transparent;
    static const Texel Black;
    static const Texel White;

    unsigned char R;
    unsigned char G;
    unsigned char B;
    unsigned char A;
};
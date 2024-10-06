export module texel;

export struct Texel
{
    static const Texel Transparent;
    static const Texel Black;
    static const Texel White;

    static const Texel Red;
    static const Texel Green;
    static const Texel Blue;

    static const Texel Yellow;
    static const Texel Magenta;
    static const Texel Cyan;

    unsigned char R;
    unsigned char G;
    unsigned char B;
    unsigned char A;
};
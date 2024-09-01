#pragma once

#include <stdint.h>

class Profiler
{
public:
    void start();
    void endFrame();

    int getFrameIndex() const;
    float getDeltaTime() const;
    float getFPS() const;

private:
    int frameIndex = -1;
    uint64_t frameStartTime = 0;
    float deltaTime = 0;
};
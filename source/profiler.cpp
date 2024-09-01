#include "profiler.h"

#include "timer.h"
#include "log.h"

void Profiler::start()
{
    frameIndex = 0;
    frameStartTime = get_elapsed_time();
    deltaTime = 0;
}

void Profiler::endFrame()
{
    auto currentTime = get_elapsed_time();
    deltaTime = static_cast<float>(currentTime - frameStartTime) / 1'000'000;

    frameIndex++;
    frameStartTime = currentTime;
}

int Profiler::getFrameIndex() const
{
    return frameIndex;
}

float Profiler::getDeltaTime() const
{
    return deltaTime;
}

float Profiler::getFPS() const
{
    return 1.0f / deltaTime;
}
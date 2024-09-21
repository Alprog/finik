export module profiler;

#include <cstdint>
import std;
import lane;

export namespace finik::profiler
{
    class Profiler
    {
    public:
        Profiler();

        void start();
        void endFrame();

        int getFrameIndex() const;
        float getDeltaTime() const;
        float getFPS() const;

        Lane& GetCpuLane();
        Lane& GetGpuLane();

    private:
        int frameIndex = -1;
        uint64_t frameStartTime = 0;
        float deltaTime = 0;
        
        Lane cpuLane;
        Timebox* frameTimebox;
        Lane gpuLane;
    };
}


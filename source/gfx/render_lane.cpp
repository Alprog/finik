module render_lane;

import render_system;
import camera;
import app;
import timebox_tracker;
import command_list;
import scene;

RenderLane::RenderLane(Scene& scene, Camera& camera, IntSize resolution)
    : scene{scene}
    , camera{camera}
{
    surface.init(resolution);
}

void RenderLane::resize(IntSize resolution)
{
    if (surface.resolution != resolution)
    {
        RenderSystem& render_system = App::GetInstance().render_system;
        render_system.get_command_queue().Flush();

        surface.resize(resolution);
        camera.AspectRatio = static_cast<float>(resolution.width) / resolution.height;
        camera.calcProjectionMatrix();
    }
}

RenderSurface& RenderLane::getSurface()
{
    return surface;
}

void RenderLane::render()
{
    RenderSystem& render_system = App::GetInstance().render_system;
    auto& commandQueue = render_system.get_command_queue();
    {
        Profile _("wait");
        commandQueue.fence->WaitForValue(fenceValue);
    }

    CommandList& commandList = render_system.getFreeCommandList();
    commandList.startRecording();

    surface.startRendering(commandList.listImpl.Get());

    RenderContext context(render_system, *commandList.listImpl.Get());
    scene.render(context, &camera);
    surface.endRendering(commandList.listImpl.Get());

    commandList.endRecording();
    commandQueue.execute(commandList);

    fenceValue = commandQueue.fence->SignalNext();
}

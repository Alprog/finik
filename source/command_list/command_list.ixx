export module command_list;

import dx;
import render_system_fwd;
import render_context;
import compute_context;

export class CommandList
{
public:
    explicit CommandList(RenderSystem& renderSystem, CommandListPool& pool, int frameIndex);
    void reset(int frameIndex);
    void returnToPool();

    void startRecording();
    void endRecording();

    int getFrameIndex() const;

    RenderContext getRenderContext()
    {
        return RenderContext(renderSystem, *listImpl.Get());
    }

    ComputeContext getComputeContext()
    {
        return ComputeContext(renderSystem, *listImpl.Get());
    }

    void Transition(ID3D12Resource* resource, D3D12_RESOURCE_STATES srcState, D3D12_RESOURCE_STATES dstState);

private:
    int addTimestampQuery();

public:
    MyPtr<ID3D12GraphicsCommandList> listImpl;
    MyPtr<ID3D12CommandAllocator> commandAllocator;

private:
    RenderSystem& renderSystem;
    CommandListPool& pool;
    int frameIndex;

    int startTimestampIndex;
    int endTimestampIndex;
};
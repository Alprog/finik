export module command_list;

import dx;
import render_system_fwd;

export class CommandList
{
public:
    explicit CommandList(RenderSystem& renderSystem, CommandListPool& pool, int frameIndex);
    void reset(int frameIndex);
    void returnToPool();

    void startRecording();
    void endRecording();

    int getFrameIndex() const;

private:
    int addTimestampQuery();

public:
    ComPtr<ID3D12GraphicsCommandList> listImpl;
    ComPtr<ID3D12CommandAllocator> commandAllocator;

private:
    RenderSystem& renderSystem;
    CommandListPool& pool;
    int frameIndex;

    int startTimestampIndex;
    int endTimestampIndex;
};
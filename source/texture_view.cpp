#include "texture_view.h"

#include "scene.h"
#include "gfx/texture.h"
#include "grid.h"
#include "tile_map.h"

import imgui;

TextureView::TextureView(const char* name, Scene& scene)
    : View {name}
    , scene {scene}
{
}

void TextureView::draw_content()
{
    auto* Texture = scene.grid->tileMap->Texture;
    D3D12_GPU_DESCRIPTOR_HANDLE handle = Texture->descriptorHandle.getGPU();

    ImTextureID textureId = (void*)handle.ptr;
    
    auto size = ImVec2(Texture->Width, Texture->Height);
    ImGui::Image(textureId, size);
}
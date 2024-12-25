module assets_view;

import imgui;
import assets;

AssetsView::AssetsView(const char* name)
    : View{ name }
{
}

void AssetsView::draw_content()
{
    auto& assets = Assets::GetInstance();

    ImGui::Text("Textures: %i", assets.Textures.size());
    for (auto& texture : assets.Textures)
    {
        ImGui::Text("%s (%i)", texture.first.c_str(), texture.second.use_count());
    }

    ImGui::NewLine();

    ImGui::Text("Shader source files: %i", assets.ShaderSourceFiles.size());
    for (auto& texture : assets.ShaderSourceFiles)
    {
        ImGui::Text("%s (%i)", texture.first.c_str(), texture.second.use_count());
    }
}
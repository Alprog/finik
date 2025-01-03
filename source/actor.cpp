module actor;

import mesh;
import material;
import texture;
import assets;

Actor::Actor()
{
    mesh = createCubeMesh();
    transformMatrix = Matrix::Identity;

    auto texture = Assets::GetInstance().get<Texture>("textures/skullbox.png");
    material = new Material("actor");
    material->Textures.append(texture);
    material->RefreshBuffer();
}
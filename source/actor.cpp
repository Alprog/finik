module actor;

import mesh;
import material;
import texture;
import assets;

Actor::Actor()
{
    mesh = createCubeMesh();
    transformMatrix = Matrix::Identity;

    auto texture = Assets::GetInstance().GetTexture("textures/skullbox.png");
    material = new Material("actor");
    material->Textures.push_back(texture);
    material->RefreshBuffer();

    Assets::GetInstance().GetTexture("C:/finik/textures/head.png");
    Assets::GetInstance().GetTexture("C:/finik/textures/head.png");
}
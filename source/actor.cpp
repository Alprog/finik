module actor;

import mesh;
import material;
import texture;

Actor::Actor()
{
    mesh = createCubeMesh();
    transformMatrix = Matrix::Identity;

    auto texture = new Texture("C:/finik/textures/skullbox.png");
    material = new Material("actor");
    material->Textures.push_back(texture);
    material->RefreshBuffer();
}
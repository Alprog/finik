export module material_manager;

import core;
import constant_buffer;
import material;

export class MaterialManager
{
    void Register(Material* material);
    void Unregister(Material* material);

    std::vector<Material*> materials;
};
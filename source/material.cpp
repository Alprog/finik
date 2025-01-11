module material;

import material_manager;

Material::Material(std::string name)
    : Name{name}
{
    Index = MaterialManager::GetInstance().Register(this);
}

Material::~Material()
{
    MaterialManager::GetInstance().Unregister(this);
}

void Material::RefreshBuffer()
{
    MaterialManager::GetInstance().WriteToBuffer(this);
}

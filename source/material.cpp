module material;

static int32 Counter = 0;

Material::Material()
    : Index { Counter++ }
{

}

Material::~Material()
{

}

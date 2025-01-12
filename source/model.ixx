export module model;

import core;
import asset;
import obj_loader;
import mesh;
import mesh_builder;
import vertex;

export class Model : public Asset
{
public:
    using Asset::Asset;

    Vector3 to_z_up(const Vector3 v)
    {
        return {v.x, -v.z, v.y};
    }

    void hot_reload(ByteBlob& blob) override
    {
        ObjLoader loader;
        loader.load(blob.asString());

        MeshBuilder builder;
        for (auto& face : loader.faces)
        {
            Array<StandardVertex> vertices;
            vertices.reserve(face.count());
            for (auto& desc : face)
            {
                StandardVertex& vertex = vertices.emplace_back();
                vertex.position = to_z_up(loader.positions[desc.pi]);
                vertex.normal = to_z_up(loader.normals[desc.ni]);
                vertex.texCoord = loader.tex_coords[desc.ti];
            }
            builder.addTriangleFan(vertices);
        }

        mesh = builder.Build();
    }

    Mesh* mesh = nullptr;
};
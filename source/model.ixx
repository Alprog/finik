export module model;

import core;
import asset;
import obj_loader;
import mesh;
import mesh_builder;
import vertex;

export class Model : public Asset
{
    using Asset::Asset;

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
                vertex.position = loader.positions[desc.pi];
                vertex.normal = loader.normals[desc.ni];
                vertex.texCoord = loader.tex_coords[desc.ti];
            }
            builder.addTriangleFan(vertices);
        }
    }

    Mesh mesh;
};
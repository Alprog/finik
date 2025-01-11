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
            Array<int32> indices;
            indices.reserve(face.count());
            for (auto& desc : face)
            {
                StandardVertex vertex;
                vertex.position = loader.positions[desc.pi];
                vertex.normal = loader.normals[desc.ni];
                vertex.texCoord = loader.tex_coords[desc.ti];

                int32 vertexIndex = builder.addVertex(vertex);
                indices.append(vertexIndex);
            }

            builder.addIndex(indices[0]);
            builder.addIndex(indices[1]);
            builder.addIndex(indices[2]);

            if (indices.count() >= 4)
            {
                builder.addIndex(indices[0]);
                builder.addIndex(indices[2]);
                builder.addIndex(indices[3]);
            }
        }
    }

    Mesh mesh;
};
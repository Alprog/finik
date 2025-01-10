export module obj_loader;

import core;

export class ObjLoader
{
public:
    void load(String text)
    {
        Array<String> lines = text.split("\n");
        for (auto& line : lines)
        {
            auto arr = line.get_trimmed().split(" ");
            if (arr[0] == "v")
            {
                auto x = std::stof(arr[1]);
                auto y = std::stof(arr[2]);
                auto z = std::stof(arr[3]);
                vertices.emplace_back(x, y, z);
            }

            if (arr[0] == "vn")
            {
                auto x = std::stof(arr[1]);
                auto y = std::stof(arr[2]);
                auto z = std::stof(arr[3]);
                normals.emplace_back(x, y, z);
            }

            if (arr[0] == "vt")
            {
                auto u = std::stof(arr[1]);
                auto v = std::stof(arr[2]);
                tex_coords.emplace_back(u, v);
            }

            //if (arr[0] == "f")
            //{
            //    auto list = new Array<int>();
            //    for (int i = 1; i < arr.count(); i++)
            //    {
            //        list.Add(int.Parse(arr[i].Split('/')[0]) - 1);
            //    }
            //    Faces.Add(new Face(list, CurrentMaterial));
            //}

            //if (arr[0] == "mtllib")
            //{
            //    var directoryPath = new FileInfo(objPath).Directory.FullName;
            //    var mtlPath = Path.Combine(directoryPath, arr[1]);
            //    LoadMaterialLibrary(mtlPath);
            //}

            //if (arr[0] == "usemtl")
            //{
            //    CurrentMaterial = Materials[arr[1]];
            //}
        }

        return;
    }

private:
    Array<Vector3> vertices;
    Array<Vector3> normals;
    Array<Vector2> tex_coords;
};
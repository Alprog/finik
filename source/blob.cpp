module blob;

Blob::Blob(Path path)
{
    std::ifstream fstream(path.c_str(), std::ios::binary);
    std::stringstream sstream;
    sstream << fstream.rdbuf();
    this->str = sstream.str();
}

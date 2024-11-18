export module hot_reloader;

import core;
import blob;

export class HotReloader : public Singleton<HotReloader>
{
public:
    using Callback = std::function<void(Blob& blob)>;

    void Add(Path filePath, const Callback& Callback)
    {
        Callbacks[filePath] = Callback;
    }

    void Remove(Path filePath)
    {
        Callbacks.erase(filePath);
    }

    void Update()
    {

    }

    std::unordered_set<Path> ChangedFiles;
    std::unordered_map<Path, Callback> Callbacks;
};
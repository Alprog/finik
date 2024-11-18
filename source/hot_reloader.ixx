export module hot_reloader;

import core;
import blob;
import file_watcher;

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
        for (auto& changedPath : FileWatcher::GetInstance().ChangedFiles)
        {
            auto it = Callbacks.find(changedPath);
            if (it != std::end(Callbacks))
            {
                Blob blob(changedPath);
                it->second(blob);
            }
        }
        FileWatcher::GetInstance().ChangedFiles.clear();
    }

    std::unordered_map<Path, Callback> Callbacks;
};
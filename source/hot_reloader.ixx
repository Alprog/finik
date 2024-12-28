export module hot_reloader;

import core;
import byte_blob;
import file_watcher;

export class HotReloader : public Singleton<HotReloader>
{
public:
    using Callback = std::function<void(ByteBlob& blob)>;

    void Add(Path filePath, const Callback& Callback)
    {
        Callbacks[filePath] = Callback;
    }

    void Remove(Path filePath)
    {
        Callbacks.remove(filePath);
    }

    void Update()
    {
        for (auto& changedPath : FileWatcher::GetInstance().ChangedFiles)
        {
            auto it = Callbacks.find_value(changedPath);
            if (it)
            {
                ByteBlob blob(changedPath);
                (*it)(blob);
            }
        }
        FileWatcher::GetInstance().ChangedFiles.clear();
    }

    HashMap<Path, Callback> Callbacks;
};
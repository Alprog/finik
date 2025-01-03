module;
#include "Windows.h"
#include "asserts.h"
export module asset_folder;

import core;
import asset_bundle;
import asset_path;

struct DirectoryWatcher
{
    Path directoryPath;
    HANDLE file;
    byte changeBuffer[1024];
    OVERLAPPED overlapped;

    DirectoryWatcher(Path path)
        : directoryPath{ path }
    {
        file = CreateFileA(path.c_str(),
            FILE_LIST_DIRECTORY,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            NULL,
            OPEN_EXISTING,
            FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
            NULL);

        overlapped.hEvent = CreateEvent(NULL, FALSE, 0, NULL);

        BOOL success = ReadDirectoryChangesW(
            file, changeBuffer, 1024, FALSE,
            FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE,
            NULL, &overlapped, NULL);
    }

    void update(std::function<void(AssetPath, int32)> callback)
    {
        DWORD result = WaitForSingleObject(overlapped.hEvent, 0);
        if (result == WAIT_OBJECT_0)
        {
            DWORD bytes_transferred;
            GetOverlappedResult(file, &overlapped, &bytes_transferred, FALSE);

            FILE_NOTIFY_INFORMATION* event = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(changeBuffer);

            for (;;)
            {
                DWORD nameLength = event->FileNameLength / sizeof(wchar_t);
                std::string fileName = std::string(&event->FileName[0], &event->FileName[nameLength]);
                callback(fileName, event->Action);

                // Are there more events to handle?
                if (event->NextEntryOffset) {
                    *((uint8_t**)&event) += event->NextEntryOffset;
                }
                else {
                    break;
                }
            }

            // Queue the next event
            BOOL success = ReadDirectoryChangesW(
                file, changeBuffer, 1024, FALSE,
                FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE,
                NULL, &overlapped, NULL);
        }

    }
};


export class AssetFolder : public AssetBundle
{
public:
    AssetFolder(Path folder_path)
        : folder_path{ folder_path }
        , watcher{ folder_path }
    {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(folder_path.str()))
        {
            if (entry.is_regular_file())
            {
                const Path file_path = entry.path();
                const AssetPath relative_path = file_path.getRelativeTo(folder_path);
                entries[relative_path] = AssetStatus::Added;
            }
        }
    }

    void update() override
    {
        watcher.update([this](AssetPath asset_path, int32 Action) 
        {
            switch (Action)
            {
            case FILE_ACTION_ADDED:
            case FILE_ACTION_RENAMED_NEW_NAME:
            {
                entries[asset_path] = entries.contains(asset_path) ? AssetStatus::Modified : AssetStatus::Added;
                break;
            }

            case FILE_ACTION_MODIFIED:
                entries[asset_path] = AssetStatus::Modified;
                break;

            case FILE_ACTION_REMOVED:
            case FILE_ACTION_RENAMED_OLD_NAME:
                entries[asset_path] = AssetStatus::Removing;
                break;
            }

            synced = false;
        });
    }

    Path get_folder_path() const
    {
        return folder_path;
    }

private:
    Path folder_path;
    DirectoryWatcher watcher;
};
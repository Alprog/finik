module;
#include "Windows.h"
#include "asserts.h"
export module asset_folder;

import core;
import asset_bundle;
import asset_path;

//struct DirectoryWatcher
//{
//    Path directoryPath;
//    HANDLE file;
//    byte changeBuffer[1024];
//    OVERLAPPED overlapped;
//
//    DirectoryWatcher(Path path)
//        : directoryPath{ path }
//    {
//        file = CreateFileA(path.c_str(),
//            FILE_LIST_DIRECTORY,
//            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
//            NULL,
//            OPEN_EXISTING,
//            FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
//            NULL);
//
//        overlapped.hEvent = CreateEvent(NULL, FALSE, 0, NULL);
//
//        BOOL success = ReadDirectoryChangesW(
//            file, changeBuffer, 1024, FALSE,
//            FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE,
//            NULL, &overlapped, NULL);
//    }
//
//    void update(std::function<void(AssetPath, int32)> callback)
//    {
//        DWORD result = WaitForSingleObject(overlapped.hEvent, 0);
//        if (result == WAIT_OBJECT_0)
//        {
//            DWORD bytes_transferred;
//            GetOverlappedResult(file, &overlapped, &bytes_transferred, FALSE);
//
//            FILE_NOTIFY_INFORMATION* event = reinterpret_cast<FILE_NOTIFY_INFORMATION*>(changeBuffer);
//
//            for (;;)
//            {
//                DWORD nameLength = event->FileNameLength / sizeof(wchar_t);
//                std::string fileName = std::string(&event->FileName[0], &event->FileName[nameLength]);
//                callback(fileName, event->Action);
//
//                // Are there more events to handle?
//                if (event->NextEntryOffset) {
//                    *((uint8_t**)&event) += event->NextEntryOffset;
//                }
//                else {
//                    break;
//                }
//            }
//
//            // Queue the next event
//            BOOL success = ReadDirectoryChangesW(
//                file, changeBuffer, 1024, FALSE,
//                FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE,
//                NULL, &overlapped, NULL);
//        }
//
//    }
//};

struct DirectoryChangeWatcher
{
    DirectoryChangeWatcher(Path path)
    {
        constexpr int32 flags = FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE;
        change_handle = FindFirstChangeNotificationA(path.c_str(), true, flags);
    }

    bool has_changes()
    {
        bool changed = false;
        while (WaitForSingleObject(change_handle, 0) == WAIT_OBJECT_0)
        {
            changed = true;
            FindNextChangeNotification(change_handle);
        }

        return changed;
    }

    HANDLE change_handle;
};

export class AssetFolder : public AssetBundle
{
public:
    AssetFolder(Path folder_path)
        : folder_path{ folder_path }
        , watcher{ folder_path }
    {
        rescan_folder();
    }

    void scan_folder()
    {

    }

    void merge()
    {

    }

    void rescan_folder()
    {
        //const bool was_empty = entries.empty();

        //for (auto& pair : entries)
        //{
        //    pair.second.status = AssetStatus::Removing;
        //}

        //for (const auto& entry : std::filesystem::recursive_directory_iterator(folder_path.str()))
        //{
        //    if (entry.is_regular_file())
        //    {
        //        const Path file_path = entry.path();
        //        const AssetPath relative_path = file_path.getRelativeTo(folder_path);
        //        const auto time = std::filesystem::last_write_time(file_path.c_str());

        //        if (!was_empty)
        //        {
        //            auto it = entries.find_value(relative_path);
        //            if (it)
        //            {
        //                entries[relative_path] = { it->time == time ? AssetStatus::Synced : AssetStatus::Modified, time };
        //                continue;
        //            }
        //        }

        //        entries[relative_path] = { AssetStatus::Added, time };
        //    }
        //}

        //synced = !entries.contains([](auto& entry) { return entry.second.status != AssetStatus::Synced; });
    }

    void update() override
    {
        if (watcher.has_changes())
        {
            rescan_folder();
        }
    }

    Path get_folder_path() const
    {
        return folder_path;
    }

private:
    Path folder_path;
    DirectoryChangeWatcher watcher;
};
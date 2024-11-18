module;
#include "Windows.h"
#include "asserts.h"
export module file_watcher;

import core;

struct WatchedDirectory
{
    Path directoryPath;
    HANDLE file;
    byte changeBuffer[1024];
    OVERLAPPED overlapped;

    WatchedDirectory(Path path)
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

    void Update(std::unordered_set<Path>& changedFiles)
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

                switch (event->Action)
                {
                    case FILE_ACTION_MODIFIED:
                    case FILE_ACTION_RENAMED_NEW_NAME:
                    case FILE_ACTION_ADDED:
                    {
                        changedFiles.insert(Path::combine(directoryPath, fileName));
                    }
                }

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

export class FileWatcher : public Singleton<FileWatcher>
{
public:
    void WatchFile(Path filePath)
    {
        WatchDirectory(filePath.getParentPath());
    }

    void Update()
    {
        for (auto& Directory : WatchedDirectories)
        {
            Directory.second->Update(ChangedFiles);
        }
    }

    void WatchDirectory(Path directoryPath)
    {
        if (!WatchedDirectories.contains(directoryPath))
        {
            WatchedDirectories.emplace(directoryPath, new WatchedDirectory{ directoryPath });
        }
    }

    std::unordered_map<Path, WatchedDirectory*> WatchedDirectories;
    std::unordered_set<Path> ChangedFiles;
};
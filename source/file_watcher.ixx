module;
#include "Windows.h"
export module file_watcher;

import core;

export class FileWatcher : public Singleton<FileWatcher>
{
    void A()
    {
        HANDLE ChangeHandle = FindFirstChangeNotificationA("C:\\finik", FALSE, FILE_NOTIFY_CHANGE_LAST_WRITE);

        DWORD Wait = WaitForSingleObject(ChangeHandle, INFINITE);
        if (Wait == WAIT_OBJECT_0)
        {
            FindNextChangeNotification(ChangeHandle);
        }
    }
};
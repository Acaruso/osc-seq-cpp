#include "windows_wrapper.hpp"

#include <windows.h>
#include <shobjidl.h>

#include <stdlib.h>

// https://docs.microsoft.com/en-us/windows/win32/learnwin32/example--the-open-dialog-box

std::string open_file_dialog()
{
    std::string path = "";

    HRESULT hr = CoInitializeEx(
        NULL,
        COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE
    );

    if (SUCCEEDED(hr)) {
        IFileOpenDialog *pFileOpen;

        // Create the FileOpenDialog object.
        hr = CoCreateInstance(
            CLSID_FileOpenDialog,
            NULL,
            CLSCTX_ALL,
            IID_IFileOpenDialog,
            reinterpret_cast<void**>(&pFileOpen)
        );

        if (SUCCEEDED(hr)) {
            // Show the Open dialog box.
            hr = pFileOpen->Show(NULL);

            // Get the file name from the dialog box.
            if (SUCCEEDED(hr)) {
                IShellItem *pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr)) {
                    PWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                    // convert wide string (?) to char array, convert that to std::string
                    char str[128];
                    wcstombs(str, pszFilePath, 128);
                    path = str;

                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();
    }
    return path;
}

std::string save_file_dialog()
{
    std::string path = "";

    HRESULT hr = CoInitializeEx(
        NULL,
        COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE
    );

    if (SUCCEEDED(hr)) {
        IFileSaveDialog *pFileSave;

        // Create the FileOpenDialog object.
        hr = CoCreateInstance(
            CLSID_FileSaveDialog,
            NULL,
            CLSCTX_ALL,
            IID_IFileSaveDialog,
            reinterpret_cast<void**>(&pFileSave)
        );

        // Set default extension
        hr = pFileSave->SetDefaultExtension(L"seq");

        if (SUCCEEDED(hr)) {
            if (SUCCEEDED(hr)) {
                // Show the Open dialog box.
                hr = pFileSave->Show(NULL);

                // Get the file name from the dialog box.
                if (SUCCEEDED(hr)) {
                    IShellItem *pItem;
                    hr = pFileSave->GetResult(&pItem);
                    if (SUCCEEDED(hr)) {
                        PWSTR pszFilePath;
                        hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                        // convert wide string (?) to char array, convert that to std::string
                        char str[128];
                        wcstombs(str, pszFilePath, 128);
                        path = str;

                        pItem->Release();
                    }
                }
                pFileSave->Release();
            }
        }
        CoUninitialize();
    }
    return path;
}

# Questions
deviceTTSrelease的提交怎么直接update了？

xwin.cpp 
copyfile deletefile movefile； OK
GetTempFileName ; OK


117行 struct XWIN_THREADHANDLE ；struct XWIN_EVENTHANDLE；struct XWIN_SEM_HANDLE
23行 #include <pthread.h>
2305行 struct XWIN_HANDLE，CreateFileW ,GetFileType；CloseHandle

CreateFileMappingW？？

2305
#ifdef _MSC_VER
struct XWIN_HANDLE
{
    enum
    {
        FILE, FILEMAPPING, THREAD, EVENT, SEM
    } m_eType;

    void* m_p;
    BOOL m_fOwner;
    DWORD exitCode;
};

DWORD g_xwinAPILastError = 0;

WINBASEAPI
VOID
WINAPI
SetLastError(
    _In_ DWORD dwErrCode
)
{
    g_xwinAPILastError = dwErrCode;
}

EXTERN_C
WINBASEAPI
HANDLE
WINAPI
CreateFileW(
    _In_ LPCWSTR lpFileName,
    _In_ DWORD dwDesiredAccess,
    _In_ DWORD dwShareMode,
    _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    _In_ DWORD dwCreationDisposition,
    _In_ DWORD dwFlagsAndAttributes,
    _In_opt_ HANDLE hTemplateFile
)
{
    if (lpFileName == NULL)
    {
        return INVALID_HANDLE_VALUE;
    }
    //check exist
    bool isExist = true;

    FILE* file;
    if (dwDesiredAccess == GENERIC_WRITE)
        file = _wfopen(lpFileName, _T("wb+"));
    else
        file = _wfopen(lpFileName, _T("rb"));

    if (file == NULL)
    {
        isExist = false;
    }

    if (isExist)
    {
        XWIN_HANDLE* pWinHandle = new XWIN_HANDLE;
        pWinHandle->m_eType = XWIN_HANDLE::FILE;
        pWinHandle->m_fOwner = TRUE;
        pWinHandle->m_p = file;
        return pWinHandle;
    }
    else
    {
        SetLastError(ERROR_FILE_NOT_FOUND);
        return INVALID_HANDLE_VALUE;
    }
}

EXTERN_C
WINBASEAPI
DWORD
WINAPI
GetFileType(
    _In_ HANDLE hFile
)
{
    return FILE_TYPE_DISK;
}

EXTERN_C
BOOL
WINAPI
CloseHandle(
    _In_ HANDLE hObject
)
{
    if (hObject != NULL)
    {
        XWIN_HANDLE* pHandle = (XWIN_HANDLE*)hObject;
        if (pHandle->m_fOwner == TRUE)
        {
            switch (pHandle->m_eType)
            {
            case XWIN_HANDLE::FILE:
                fclose((FILE*)pHandle->m_p);
                break;
            case XWIN_HANDLE::THREAD:
                delete (XWIN_THREADHANDLE*)pHandle->m_p;
                break;
            case XWIN_HANDLE::EVENT:
                delete (XWIN_EVENTHANDLE*)pHandle->m_p;
                break;
            default:
                break;
            }
        }

        delete pHandle;
    }

    return TRUE;
}
#endif
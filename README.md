# Questions
没法remove掉

xwin.cpp 
copyfile deletefile movefile； OK

  HRESULT hr = StringCchPrintfW(wzTempBrkFileName, ARRAYSIZE(wzTempBrkFileName), _T("%s%s%s"), (const WCHAR*)strTempPathBuffer, pEngine->GetVoiceFontName(),_T(".BRK.bak"));
        UTF_VERIFY_FO(SUCCEEDED(hr));

 FILE* fp1;
    fp1 = fopen("./testdata/RUSVoiceFont/1033.BRK", "rb");
    fclose(fp1);
    if(remove("./testdata/RUSVoiceFont/1033.BRK")==0)
    printf("Wooo");


失败，不能加下面的：
117行 struct XWIN_THREADHANDLE ；struct XWIN_EVENTHANDLE；struct XWIN_SEM_HANDLE
23行 #include <pthread.h>
2305行 struct XWIN_HANDLE，CreateFileW ,GetFileType；CloseHandle

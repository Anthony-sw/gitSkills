# Questions
deviceTTSrelease的提交怎么直接update了？
没法remove掉

xwin.cpp 
copyfile deletefile movefile； OK
GetTempFileName ; OK



失败，不能加下面的：
117行 struct XWIN_THREADHANDLE ；struct XWIN_EVENTHANDLE；struct XWIN_SEM_HANDLE
23行 #include <pthread.h>
2305行 struct XWIN_HANDLE，CreateFileW ,GetFileType；CloseHandle

204行 EmbeddedSpeechConfig
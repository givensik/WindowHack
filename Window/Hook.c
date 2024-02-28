#include <windows.h>

LRESULT FAR PASCAL WndProc (HWND, UINT, UINT, LONG);

int APIENTRY WinMain (HANDLE hInstance, HANDLE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow){
    static char szAppName[] = "Hello Win";
    MSG msg;
    HWND hwnd;
    WNDCLASS wndclass;

    if(!hPrevInstance){
        wndclass.style = CS_HREDRAW | CS_VREDRAW;
        wndclass.lpfnWndProc = WndProc; // 윈도우로 메시지가 왔을 때 그 메시지를 처리할 처리 함수
        wndclass.cbClsExtra = 0; 
        wndclass.cbWndExtra = 0;
        wndclass.hInstance = hInstance; // 윈도우가 자리잡고 있는 메모리(Instance)의 첫 주소 (Win16 프로그램과 호환성을 위해 존재)
        wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
        wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        wndclass.lpszMenuName = szAppName;
        wndclass.lpszClassName = szAppName;

        RegisterClass(&wndclass);
    }

    hwnd = CreateWindow (szAppName, "Hello Win Demo", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    ShowWindow (hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while( GetMessage(&msg, NULL, 0, 0) )
    {
        TranslateMessage(&msg); // 받은 메시지를 번역
        DispatchMessage(&msg); // 번역한 메시지를 처리

    }

    return msg.wParam;

}

LRESULT FAR PASCAL WndProc (HWND hwnd, UINT message, UINT wParam, LONG lParam){
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;
    HOOKPROC hGetMsgProc;
    static HINSTANCE hinstDll;
    static HHOOK hKeyHook;
    static int count = 0;

    switch (message)
    {
        case WM_CREATE:
            hinstDll = LoadLibrary("\\MStrack.dll");

            if(!hinstDll){
                ExitProcess(1);
            }

            hGetMsgProc = (HOOKPROC)GetProcAddress(hinstDll, "GetMsgProc");
            hKeyHook = SetWindowsHookEx(WH_GETMESSAGE, hGetMsgProc, hinstDll, 0);
            if(!hKeyHook){
                FreeLibrary(hinstDll);
                ExitProcess(1);
            }
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

    }

    // 
    return DefWindowProc (hwnd, message, wParam, lParam);

}
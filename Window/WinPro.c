/*
    윈도우에 어떤 메시지라도 발생하면 불리게 할 DLL 예제
*/
#include <windows.h>

LRESULT FAR PASCAL WndProc(HWND, UINT, UINT, LONG);

// 윈도우를 만들고 시동거는 부분
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow){
    
    
    static char szAppName[] = "Hello Win";
    MSG msg;
    HWND hwnd;
    
    // 어떤 윈도우를 만들 것인지 적어두는 부분
    WNDCLASS wndclass;

    if(!hPrevInstance)
    {
        wndclass.style = CS_HREDRAW | CS_VREDRAW;
        wndclass.lpfnWndProc = WndProc; // 윈도우로 메시지가 왔을 때 그 메시지를 처리할 처리 함수
        wndclass.cbClsExtra = 0; 
        wndclass.cbWndExtra = 0;
        wndclass.hInstance = hInstance; // 윈도우가 자리잡고 있는 메모리(Instance)의 첫 주소 (Win16 프로그램과 호환성을 위해 존재)
        wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wndclass.hCursor = LoadCursor (NULL, IDC_ARROW);
        wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        wndclass.lpszMenuName = szAppName;
        wndclass.lpszClassName = szAppName;

        RegisterClass (&wndclass);
    }
    
    /*
        윈도우를 만드는 부분
        리턴값으로 윈도우를 운전할 수 있는 핸들을 윈도우가 준다.

    */ 
    hwnd = CreateWindow (szAppName, "Hello Win Demo", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    ShowWindow (hwnd, nCmdShow);
    UpdateWindow(hwnd);

    /*
        메시지를 받는 부분
    */
    while( GetMessage(&msg, NULL, 0, 0) )
    {
        TranslateMessage(&msg); // 받은 메시지를 번역
        DispatchMessage(&msg); // 번역한 메시지를 처리

    }

    return msg.wParam;

}

/*
    메시지를 처리하는 부분 -> 프로시저
    파라미터
    1. HWND hwnd : 만든 윈도우에 관한 핸들
    2,3,4 : 윈도우가 보내오는 메시지에 관련된 것들 (ex: 마우스 왼쪽 클릭 -> 2 : WM_LBUTTONDOWN, 3: x,y 좌표, 4: 사용 X) 

*/
LRESULT FAR PASCAL WndProc (HWND hwnd, UINT message, UINT wParam, LONG lParam){
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;

    switch (message)
    {
        // 다시 그릴 필요가 있을 때
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            GetClientRect(hwnd, &rect);
            DrawText(hdc, "Hello, Windows!", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            EndPaint(hwnd, &ps);
            return 0;
        
        // 윈도우가 수명을 다하고 죽을 때
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    // 
    return DefWindowProc (hwnd, message, wParam, lParam);

}
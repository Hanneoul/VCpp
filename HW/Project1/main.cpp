#include <windows.h>

// 전역 변수
HINSTANCE hInst;
HWND hMainWnd;
const int windowWidth = 800;
const int windowHeight = 480;
const int margin = 8;
const int padding = 8;
const int numButtons = 5;
const int buttonSize = (windowWidth - 2 * margin - (numButtons + 1) * padding) / numButtons;

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        // 여러 개의 버튼 생성
        for (int i = 0; i < numButtons; ++i)
        {
            HWND hButton = CreateWindow(L"BUTTON", L"Button", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                margin + i * (buttonSize + padding), windowHeight - margin - buttonSize,
                buttonSize, buttonSize, hWnd, (HMENU)(i + 1), hInst, NULL);
        }
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // 투명한 사각형 그리기
        HBRUSH transparentBrush = CreateSolidBrush(RGB(255, 255, 255));
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);
        Rectangle(hdc, margin, margin, windowWidth - margin, windowHeight - margin);
        SelectObject(hdc, oldBrush);
        DeleteObject(transparentBrush);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 메인 함수
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    hInst = hInstance;

    WNDCLASSEX wcex;
    memset(&wcex, 0, sizeof(wcex));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = L"TransparentWindowWithButtons";
    RegisterClassEx(&wcex);

    hMainWnd = CreateWindow(L"TransparentWindowWithButtons", L"투명한 윈도우와 버튼들", WS_OVERLAPPEDWINDOW,
        100, 100, windowWidth, windowHeight, NULL, NULL, hInstance, NULL);

    if (!hMainWnd)
        return FALSE;

    ShowWindow(hMainWnd, nCmdShow);
    UpdateWindow(hMainWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#include "gameheader.h"

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Inversus";
LPCTSTR lpszWindowName = L"Inversus";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
    HWND hWnd;
    MSG Message;
    WNDCLASSEX WndClass;
    g_hInst = hInstance;

    WndClass.cbSize = sizeof(WndClass);
    WndClass.style = CS_HREDRAW | CS_VREDRAW;
    WndClass.lpfnWndProc = (WNDPROC)WndProc;
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hInstance = hInstance;
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WndClass.lpszMenuName = NULL;
    WndClass.lpszClassName = lpszClass;
    WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&WndClass);

    hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&Message, 0, 0, 0))
    {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }
    return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc, mdc;
    HBITMAP backBit;
    RECT bufferRT;

    Map map;

    switch (iMessage)
    {
    case WM_CREATE:

        break;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        GetClientRect(hWnd, &bufferRT);
        mdc = CreateCompatibleDC(hdc);
        backBit = CreateCompatibleBitmap(hdc, bufferRT.right, bufferRT.bottom);
        SelectObject(mdc, (HBITMAP)backBit);
        PatBlt(mdc, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);

        map.map_change(1);
        std::cout << "그리기 전\n";
        map.map_draw(mdc);
        std::cout << "맵 그리기\n";
        // HBRUSH hBrush, oldBrush;
        // HPEN hPen, oldPen;

        // for (int i = 0; i < 20; ++i)
        //     for (int j = 0; j < 15; ++j)
        //     {
        //         if (Normal_Mode[j][i] == 0)
        //         {
        //             hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
        //             oldPen = (HPEN)SelectObject(mdc, hPen);
        //             hBrush = CreateSolidBrush(RGB(255, 255, 255));
        //             oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
        //             Rectangle(mdc, 40 * j, 25 * i, 40 * (j + 1), 25 * (i + 1));
        //             SelectObject(mdc, oldBrush);
        //             DeleteObject(hBrush);
        //             SelectObject(mdc, oldPen);
        //             DeleteObject(hPen);
        //         }
        //         else if (Normal_Mode[j][i] == 1)
        //         {
        //             hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
        //             oldPen = (HPEN)SelectObject(mdc, hPen);
        //             hBrush = CreateSolidBrush(RGB(0, 0, 0));
        //             oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
        //             Rectangle(mdc, 40 * j, 25 * i, 40 * (j + 1), 25 * (i + 1));
        //             SelectObject(mdc, oldBrush);
        //             DeleteObject(hBrush);
        //             SelectObject(mdc, oldPen);
        //             DeleteObject(hPen);
        //         }
        //     }

        GetClientRect(hWnd, &bufferRT);
        BitBlt(hdc, 0, 0, bufferRT.right, bufferRT.bottom, mdc, 0, 0, SRCCOPY);
        DeleteObject(backBit);
        DeleteDC(mdc);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
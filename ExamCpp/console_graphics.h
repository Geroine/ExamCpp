#pragma once
#include <windows.h>

void SetColorBgTex(int Bg = 0, int Tex = 15) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Bg = Bg << 4 | Tex;
    SetConsoleTextAttribute(hConsole, Bg);
}
void SetConsCurPos(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { (short)x, (short)y };
    SetConsoleCursorPosition(hConsole, coord);
}
void SetConsWinSize(int XSize = 20, int YSize = 10) {
    HWND hWnd = GetForegroundWindow();
    HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SetWindowPos(hWnd, NULL, 0, 0, XSize, YSize, NULL);
    SMALL_RECT windowSize;
    windowSize.Bottom = YSize;
    windowSize.Left = 0;
    windowSize.Right = XSize;
    windowSize.Top = 0;
    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
    COORD bufferSize = { (short)XSize + 1, (short)YSize + 1 };
    SetConsoleScreenBufferSize(wHnd, bufferSize);
    SetColorBgTex(0,15);
}
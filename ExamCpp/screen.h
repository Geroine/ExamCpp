#pragma once

#include <iostream>
#include <vector>

using namespace std;

enum eConsoleColor
{
	CC_Black = 0,
	CC_DarkBlue = 1,
	CC_DarkGreen = 2,
	CC_DarkCyan = 3,
	CC_DarkRed = 4,
	CC_DarkMagenta = 5,
	CC_DarkYellow = 6,
	CC_Gray = 7,
	CC_DarkGray = 8,
	CC_Blue = 9,
	CC_Green = 10,
	CC_Cyan = 11,
	CC_Red = 12,
	CC_Magenta = 13,
	CC_Yellow = 14,
	CC_White = 15
};

struct Symbol {
    int color;
    int background;
    char symbol;
    bool visible;
    Symbol(char s, int c, int b);
	Symbol();

    bool operator==(const Symbol& obj);
	bool operator!=(const Symbol& obj);
	Symbol& operator=(const Symbol& obj);
    bool compare(const Symbol& obj);
    void draw(int x, int y);
    friend ostream& operator<<(ostream& out, const Symbol& obj);
};

class Canvas {
protected:
    vector<vector<Symbol>> canv;
    int width;
    int height;
public:
    Canvas(int w = 50, int h = 30);
	virtual Symbol& operator()(int x, int y);
	Canvas& operator=(Canvas& obj);
	bool operator==(Canvas& obj) { return false; };
	// Не проверен
	void blit(Canvas& obj, int sx, int sy, int dx, int dy, int dWidth, int dHeight);
	virtual void blit(Canvas& obj, int sx, int sy);
	int getWidth();
	int getHeight();

};

class Screen {
protected:
    Canvas prevFrame;
    Canvas frame;
	int width,
		height;
	bool prevFrameReady;
public:
    Screen(int w, int h);
	Screen(int w, int h, Symbol bckg);

	// Не проверен
    void blit(Canvas& obj, int sx, int sy, int dx, int dy, int dWidth, int dHeight);
	void blit(Canvas& obj, int sx, int sy);
    void draw();
	int getWidth();
	int getHeight();
	operator Canvas&();

};


















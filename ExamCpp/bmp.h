#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include "screen.h"
#define UP_MIRROR 1

struct Pixel {
	unsigned   rgbBlue;
	unsigned   rgbGreen;
	unsigned   rgbRed;
	unsigned   visible;

	Pixel();
	Pixel(unsigned r, unsigned g, unsigned b, unsigned v = 1);
	bool operator==(const Pixel& obj);
	bool operator!=(const Pixel& obj);
	Pixel& operator=(const Pixel& obj);
	int getCode();
	bool compare(const Pixel& obj);

	//Symbol symbol();
};

class BMP {
	struct BMPFile {
		unsigned short    bfType;
		unsigned long   bfSize;
		unsigned short    bfReserved1;
		unsigned short    bfReserved2;
		unsigned long   bfOffBits;
	};

	struct BMPInfo {
		unsigned int    biSize;
		int             biWidth;
		int             biHeight;
		unsigned short  biPlanes;
		unsigned short  biBitCount;
		unsigned int    biCompression;
		unsigned int    biSizeImage;
		int             biXPelsPerMeter;
		int             biYPelsPerMeter;

		//short			biReserved;
		unsigned int    biClrUsed;
		unsigned int    biClrImportant;
	};

	BMPFile file;
	BMPInfo info;
	vector<vector<Pixel>> bitmap;
	bool isOpen;
	Pixel mask;

	void _open(char* filename);

	unsigned short read_u16(FILE *fp);
	unsigned int   read_u32(FILE *fp);
	int            read_s32(FILE *fp);
public:
	BMP(char* filename);
	BMP(int width = 0, int height = 0);
	BMP(char* filename, int mode);
	BMP(BMP& pic);

	BMP& operator=(BMP& obj);

	int getWidth();
	int getHeight();

	void rotate();
	void mirror();
	void upMirror();

	void setMask(Pixel p);
	Pixel getMask();
	void removeMask();

	Canvas canvas();
	Pixel& operator()(int x, int y);

};
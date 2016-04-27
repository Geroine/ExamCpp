#include "bmp.h"
#include "error.h"
#define CC_TRUE 127
#define CC_HALF 94
#define CC_1W 150
#define CC_2W 127
#define CC_3W 50

void BMP::_open(char * filename) {

	FILE* pFile = fopen(filename, "rb");
	if (!pFile) {
		isOpen = false;
	}

	file.bfType = read_u16(pFile);
	file.bfSize = read_u32(pFile);
	file.bfReserved1 = read_u16(pFile);
	file.bfReserved2 = read_u16(pFile);
	file.bfOffBits = read_u32(pFile);


	info.biSize = read_u32(pFile);
	info.biWidth = abs(read_s32(pFile));
	info.biHeight = abs(read_s32(pFile));
	info.biPlanes = read_u16(pFile);
	info.biBitCount = read_u16(pFile);
	info.biCompression = read_u32(pFile);
	info.biSizeImage = read_u32(pFile);
	info.biXPelsPerMeter = read_s32(pFile);
	info.biYPelsPerMeter = read_s32(pFile);

	//info.biReserved = read_u16(pFile);
	info.biClrUsed = read_u32(pFile);
	info.biClrImportant = read_u32(pFile);


	for (int i = 0; i < info.biHeight; i++) {
		vector<Pixel> row(info.biWidth);
		bitmap.push_back(row);
	}

	for (int i = 0; i < info.biHeight; i++) {
		for (int j = 0; j < info.biWidth; j++) {
			bitmap[i][j].rgbBlue = getc(pFile);
			bitmap[i][j].rgbGreen = getc(pFile);
			bitmap[i][j].rgbRed = getc(pFile);
			bitmap[i][j].visible = true;
		}
	}

	fclose(pFile);
	isOpen = true;
}

unsigned short BMP::read_u16(FILE * fp) {
	unsigned char b0, b1;

	b0 = getc(fp);
	b1 = getc(fp);

	return ((b1 << 8) | b0);
}

unsigned int BMP::read_u32(FILE * fp) {
	unsigned char b0, b1, b2, b3;

	b0 = getc(fp);
	b1 = getc(fp);
	b2 = getc(fp);
	b3 = getc(fp);

	return ((((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}

int BMP::read_s32(FILE * fp) {
	unsigned char b0, b1, b2, b3;

	b0 = getc(fp);
	b1 = getc(fp);
	b2 = getc(fp);
	b3 = getc(fp);

	return ((int)(((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}

BMP::BMP(char * filename) {
	_open(filename);
}

BMP::BMP(int width, int height) {
	isOpen = false;
	info.biWidth = width;
	info.biHeight = height;
	for (int i = 0; i < info.biHeight; i++) {
		vector<Pixel> row(info.biWidth);
		bitmap.push_back(row);
	}

}

BMP::BMP(char * filename, int mode) {
	_open(filename);
	if (mode == UP_MIRROR)upMirror();
}

BMP::BMP(BMP & pic) {
	BMP::operator=(pic);
}

BMP & BMP::operator=(BMP & pic) {
	if (this == &pic) return *this;
	file = pic.file;
	info = pic.info;
	bitmap = pic.bitmap;
	isOpen = pic.isOpen;
	return *this;
}

int BMP::getWidth() {
	if (!isOpen) return 0;
	return info.biWidth;
}

int BMP::getHeight() {
	if (!isOpen) return 0;
	return info.biHeight;
}

void BMP::rotate() {
	int nHeight = info.biWidth, 
		nWidth = info.biHeight;
	BMP tmp(nWidth, nHeight);
	for (int i = 0; i < info.biHeight; i++) {
		for (int j = 0; j < info.biWidth; j++) {
			tmp(i,j) = operator()(j,i);
		}
	}

	info.biHeight = nHeight;
	info.biWidth = nWidth;
	bitmap = tmp.bitmap;

}

void BMP::mirror() {
	BMP tmp(info.biWidth, info.biHeight);

	for (int i = 0; i < info.biHeight; i++) {
		for (int j = 0, k = info.biWidth - 1; j < info.biWidth; j++, k--) {
			tmp(k,i) = operator()(j,i);
		}
	}

	bitmap = tmp.bitmap;
}

void BMP::upMirror() {
	rotate();
	mirror();
	rotate();
}

Canvas BMP::canvas(Pixel key) {
	Canvas cpic(info.biWidth, info.biHeight);
	if (!isOpen) return cpic;

	char ccResult = 0;
	int ccSum;
	for (int i = 0; i < cpic.getHeight(); i++) {
		for (int j = 0; j < cpic.getWidth(); j++) {
			if (key.visible) {
				if (bitmap[i][j] != key) cpic(j,i).visible = true;
				else {
					cpic(j, i).visible = false;
					continue;
				}
			} else {
				cpic(j, i).visible = true;
			}

			ccSum = (bitmap[i][j].rgbRed +
					 bitmap[i][j].rgbGreen +
					 bitmap[i][j].rgbBlue);// / 3;


			if (bitmap[i][j].rgbRed <= 127 &&
				bitmap[i][j].rgbGreen <= 127 &&
				bitmap[i][j].rgbBlue > 127 &&
				ccSum <= CC_1W)
				ccResult = CC_DarkBlue;

			if (bitmap[i][j].rgbRed <= 127 &&
				bitmap[i][j].rgbGreen > 127 &&
				bitmap[i][j].rgbBlue <= 127 &&
				ccSum <= CC_1W)
				ccResult = CC_DarkGreen;

			if (bitmap[i][j].rgbRed <= 127 &&
				bitmap[i][j].rgbGreen > 127 &&
				bitmap[i][j].rgbBlue > 127 &&
				ccSum <= CC_HALF)
				ccResult = CC_DarkCyan;

			if (bitmap[i][j].rgbRed > 127 &&
				bitmap[i][j].rgbGreen <= 127 &&
				bitmap[i][j].rgbBlue <= 127 &&
				ccSum <= CC_1W)
				ccResult = CC_DarkRed;

			if (bitmap[i][j].rgbRed > 127 &&
				bitmap[i][j].rgbGreen <= 127 &&
				bitmap[i][j].rgbBlue > 127 &&
				ccSum <= CC_HALF)
				ccResult = CC_DarkMagenta;

			if (bitmap[i][j].rgbRed > 127 &&
				bitmap[i][j].rgbGreen > 127 &&
				bitmap[i][j].rgbBlue <= 127 &&
				ccSum <= CC_HALF)
				ccResult = CC_DarkYellow;

			if (bitmap[i][j].rgbRed <= 127 &&
				bitmap[i][j].rgbGreen <= 127 &&
				bitmap[i][j].rgbBlue > 127 &&
				ccSum > CC_1W)
				ccResult = CC_Blue;

			if (bitmap[i][j].rgbRed <= 127 &&
				bitmap[i][j].rgbGreen > 127 &&
				bitmap[i][j].rgbBlue <= 127 &&
				ccSum > CC_1W)
				ccResult = CC_Green;

			if (bitmap[i][j].rgbRed <= 127 &&
				bitmap[i][j].rgbGreen > 127 &&
				bitmap[i][j].rgbBlue > 127 &&
				ccSum > CC_HALF)
				ccResult = CC_Cyan;

			if (bitmap[i][j].rgbRed > 127 &&
				bitmap[i][j].rgbGreen <= 127 &&
				bitmap[i][j].rgbBlue <= 127 &&
				ccSum > CC_1W)
				ccResult = CC_Red;

			if (bitmap[i][j].rgbRed > 127 &&
				bitmap[i][j].rgbGreen <= 127 &&
				bitmap[i][j].rgbBlue > 127 &&
				ccSum > CC_HALF)
				ccResult = CC_Magenta;

			if (bitmap[i][j].rgbRed > 127 &&
				bitmap[i][j].rgbGreen > 127 &&
				bitmap[i][j].rgbBlue <= 127 &&
				ccSum > CC_HALF)
				ccResult = CC_Yellow;
			// Grays

			if (bitmap[i][j].rgbRed > 127 &&
				bitmap[i][j].rgbGreen > 127 &&
				bitmap[i][j].rgbBlue > 127 &&
				ccSum * 3 > 383)
				ccResult = CC_White;

			if (bitmap[i][j].rgbRed > 127 &&
				bitmap[i][j].rgbGreen > 127 &&
				bitmap[i][j].rgbBlue > 127 &&
				ccSum * 3 > 255 &&
				ccSum * 3 <= 383)
				ccResult = CC_Gray;

			if (bitmap[i][j].rgbRed <= 127 &&
				bitmap[i][j].rgbGreen <= 127 &&
				bitmap[i][j].rgbBlue <= 127 &&
				ccSum * 3 > 127 &&
				ccSum * 3 <= 255)
				ccResult = CC_Black;

			if (bitmap[i][j].rgbRed <= 127 &&
				bitmap[i][j].rgbGreen <= 127 &&
				bitmap[i][j].rgbBlue <= 127 &&
				ccSum * 3 <= 127)
				ccResult = CC_Black;

			cpic(j, i).background = ccResult;
		}
	}
	return cpic;
}

Pixel & BMP::operator()(int x, int y) {
	if (y >= bitmap.size() || y < 0) throw Error("Canvas operator(): bad 'y' argument. Taked " +
											   to_string(y) + " . And size = " + to_string(bitmap.size()));
	if (x >= bitmap[y].size() || x < 0) throw Error("Canvas operator(): bad 'x' argument. Taked " +
												  to_string(y) + " . And size = " + to_string(bitmap[y].size()));
	return bitmap[y][x];
}

Pixel::Pixel() {
	rgbBlue = 0;
	rgbGreen = 0;
	rgbRed = 0;
	visible = 0;
}

Pixel::Pixel(unsigned r, unsigned g, unsigned b, unsigned v) {
	rgbBlue = r;
	rgbGreen = g;
	rgbRed = b;
	visible = v;
}

bool Pixel::operator==(const Pixel & obj) {
	return compare(obj);
}

bool Pixel::operator!=(const Pixel & obj) {
	return !compare(obj);
}

Pixel & Pixel::operator=(const Pixel & obj) {
	if (this == &obj) return *this;
	rgbBlue = obj.rgbBlue;
	rgbGreen = obj.rgbGreen;
	rgbRed = obj.rgbRed;
	visible = obj.visible;
	return *this;
}

int Pixel::getCode() {
	return (rgbRed << 16) | (rgbGreen << 8) | (rgbBlue);
}

bool Pixel::compare(const Pixel & obj) {
	if (rgbBlue != obj.rgbBlue) return false;
	if (rgbGreen != obj.rgbGreen) return false;
	if (rgbRed != obj.rgbRed) return false;
	if (visible != obj.visible) return false;
	return true;
}

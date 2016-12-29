#ifndef IMAGE_H_
#define IMAGE_H_

#include <stdint.h>

#pragma pack(1)

namespace sksat {

struct RGB {
	unsigned r, g, b;
};

struct RGBA {
	unsigned r, g, b, a;
};

//画像基底クラス
class Image {
protected:
	bool loadflg;
	unsigned int xsize, ysize;
	unsigned char *data;
private:
	void init();
public:
	Image();
	Image(unsigned int xsize, unsigned int ysize);
	~Image();

	bool ChangeSize(unsigned int xsize, unsigned ysize);

	bool LoadRGBA(unsigned char *addr, unsigned int xsize, unsigned int ysize);
	bool LoadRGB(unsigned char *addr, unsigned int xsize, unsigned int ysize);
	bool LoadBGR(unsigned char *addr, unsigned int xsize, unsigned int ysize);

	bool IsLoaded(){ return loadflg; }
};

namespace bmp {

struct FileHeader {
	uint16_t	bfType;
	uint32_t	bfSize;
	uint16_t	bfReserved1;
	uint16_t	bfReserved2;
	uint32_t	bfOffBits;
};

struct InfoHeader {
	uint32_t	biSize;
	int32_t		biWidth;
	int32_t		biHeight;
	uint16_t	biPlanes;
	uint16_t	biBitCount;
	uint32_t	biCompression;
	uint32_t	biSizeImage;
	int32_t		biXPixPerMeter;
	int32_t		biYPixPerMeter;
	uint32_t	biClrUsed;
	uint32_t	biClrImportant;
};

struct rgbQUAD {
	unsigned char	rgbBlue;
	unsigned char	rgbGreen;
	unsigned char	rgbRed;
	unsigned char	rgbReserved;
};

};

};

#endif

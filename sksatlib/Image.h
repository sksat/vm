#ifndef IMAGE_H_
#define IMAGE_H_

namespace sksat {

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
	unsigned short	bfType;
	unsigned long	bfSize;
	unsigned short	bfReserved1;
	unsigned short	bfReserved2;
	unsigned long	bfOffBits;
};

struct InfoHeader {
	unsigned long	biSize;
	long		biWidth;
	long		biHeight;
	unsigned short	biPlanes;
	unsigned short	biBitCount;
	unsigned long	biCompression;
	unsigned long	biSizeImage;
	long		biXPixPerMeter;
	long		biYPixPerMeter;
	unsigned long	biClrUsed;
	unsigned long	biClrImportant;
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

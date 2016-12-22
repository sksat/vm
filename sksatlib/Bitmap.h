#ifndef BITMAP_H_
#define BITMAP_H_

#include <stdio.h>
#include <stdint.h>

namespace sksat{

struct Color {
	union {
		struct {
			unsigned char r, g, b;
		};
		
		struct {
			unsigned char red, green, blue;
		};
	};
};

namespace bitmap {
	#define FILE_HEADER_SIZE	14
	#define INFO_HEADER_SIZE	40
	
	#define BFTYPE			0x4d42	//"BM"
	
	struct FileHeader {
		unsigned char Type[2];
		unsigned long Size;
		unsigned short Reserved[2];
		unsigned long OffBits;
	};
	
	struct InfoHeader {
		unsigned long Size;
		long Width;
		long Height;
		unsigned short Planes;
		unsigned short BitCount;
		unsigned long Compression;
		unsigned long SizeImage;
		long XPelsPerMeter;
		long YPelsPerMeter;
		unsigned long ClrUsed;
		unsigned long ClrImportant;
	};
};

class Bitmap {
private:
	bitmap::FileHeader fh;
	bitmap::InfoHeader ih;
	
	int xsize, ysize;
public:
	
private:
	void init();
public:
	Bitmap(){ init(); }
	Bitmap(unsigned char *img, int xsize, int ysize){ init(); Load(img, xsize, ysize); }
	~Bitmap();
	
	int Load(char *fname);
	void Load(unsigned char *img, int xsize, int ysize);
	void Write(char *fname);
	void Write(FILE *fp);
	
	unsigned char* GetImgAddr();
};

}; //namespace sksat
#endif //BITMAP_H_

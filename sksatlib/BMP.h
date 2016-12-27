#ifndef BMP_H_
#define BMP_H_

#include "Image.h"

//参考：http://climbi.com/b/8796/0

#define COLOR_BIT_NUM	  8
#define COLOR_USE_NUM	256

namespace sksat {

class BMP : public Image {
private:
	bmp::FileHeader	fh;
	bmp::InfoHeader	ih;

	bmp::rgbQUAD	*palette;

	void init();
	void InitFileHeader();
	void InitInfoHeader();
	void InitPalette();
public:
	BMP();
	~BMP();
	
	void Write(const char *fname);
};

};

#endif

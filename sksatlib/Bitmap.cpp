#include "Bitmap.h"

using namespace sksat;
using namespace bitmap;

void Bitmap::init(){
	fh.Type[0]	= 'B';
	fh.Type[1]	= 'M';
	fh.Size		= 0;
	fh.Reserved[0]	= 0;
	fh.Reserved[1]	= 0;
	fh.OffBits	= 0;
	
	ih.Size		= INFO_HEADER_SIZE;
	ih.Width	= 0;
	ih.Height	= 0;
	ih.Planes	= 1;
	ih.BitCount	= 16;
	ih.Compression	= 3;
	ih.SizeImage	= 0;
	ih.XPelsPerMeter= 0;
	ih.YPelsPerMeter= 0;
	ih.ClrUsed	= 0;
	ih.ClrImportant	= 0;
}


void Bitmap::Load(unsigned char *img, int xsize, int ysize){
	if(this->img == NULL) return;
	this->img	= img;
	ih.Width	= xsize;
	ih.Height	= ysize;
	
}



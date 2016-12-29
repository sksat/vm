#include <stdio.h>

#include "BMP.h"

using namespace sksat;
using namespace bmp;

void BMP::init(){
	InitFileHeader();
	InitInfoHeader();

	InitPalette();
}

BMP::BMP(){
	init();
}

BMP::~BMP(){
	delete palette;
}

void BMP::InitFileHeader(){
	fh.bfType		= 'B' | ('M' << 8);
	fh.bfSize		= sizeof(FileHeader) + sizeof(InfoHeader)
					+ (sizeof(rgbQUAD) * COLOR_USE_NUM) + (xsize * ysize);
	fh.bfReserved1		= 0;
	fh.bfReserved2		= 0;
	fh.bfOffBits		= sizeof(FileHeader) + sizeof(InfoHeader)
					+ sizeof(rgbQUAD) * COLOR_USE_NUM;
	
	return;
}

void BMP::InitInfoHeader(){
	ih.biSize		= 40;		//40固定
	ih.biWidth		= xsize;
	ih.biHeight		= ysize;
	ih.biPlanes		= 1;		//1固定
	ih.biBitCount		= COLOR_BIT_NUM;
	ih.biCompression	= 0;		//無圧縮
	ih.biSizeImage		= (xsize * ysize * COLOR_BIT_NUM);
	ih.biXPixPerMeter	= 3780;
	ih.biYPixPerMeter	= 3780;
	ih.biClrUsed		= 0;
	ih.biClrImportant	= 0;
	
	return;
}

void BMP::InitPalette(){
	rgbQUAD	table_bgra[16] = {
		{0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0xff, 0x00},
		{0x00, 0xff, 0x00, 0x00},
		{0x00, 0xff, 0xff, 0x00},
		{0x00, 0x00, 0xff, 0x00},
		{0xff, 0x00, 0xff, 0x00},
		{0xff, 0xff, 0x00, 0x00},
		{0xff, 0xff, 0xff, 0x00},
		{0xc6, 0xc6, 0xc6, 0x00},
		{0x00, 0x00, 0x84, 0x00},
		{0x00, 0x84, 0x00, 0x00},
		{0x00, 0x84, 0x84, 0x00},
		{0x84, 0x00, 0x00, 0x00},
		{0x84, 0x00, 0x84, 0x00},
		{0x84, 0x84, 0x00, 0x00},
		{0x84, 0x84, 0x84, 0x00}
	};

	palette 	= new rgbQUAD[COLOR_USE_NUM];

	for(int i=0;i<16;i++){
		palette[i] = table_bgra[i];
	}

	return;
}

void BMP::UpdateHeader(){
	fh.bfSize		= 14 + 40//sizeof(FileHeader) + sizeof(InfoHeader)
					+ (xsize * ysize * COLOR_BIT_NUM);
	ih.biWidth		= xsize;
	ih.biHeight		= ysize;
	ih.biSizeImage		= (xsize * ysize * COLOR_BIT_NUM);
}

bool BMP::IsSame(unsigned char *rgba, rgbQUAD *quad){
	if(rgba[0] != quad->rgbRed)	return false;
	if(rgba[1] != quad->rgbGreen)	return false;
	if(rgba[2] != quad->rgbBlue)	return false;
	if(rgba[3] != quad->rgbReserved)return false;

	return true;
}

int BMP::GetPaletteNum(unsigned char *rgba){
	for(int i=0;i<COLOR_USE_NUM;i++){
		if(IsSame(rgba, &(palette[i]))){
			return i;
		}
	}
}

void BMP::Write(const char *fname){
	FILE *fp;

	UpdateHeader();

	fp = fopen(fname, "wb");
	if(fp == NULL){
		return;
	}
	
	fwrite(&fh, sizeof(FileHeader), 1, fp);
	fwrite(&ih, sizeof(InfoHeader), 1, fp);
	fwrite(&palette, sizeof(rgbQUAD), COLOR_USE_NUM, fp);
	
//	fwrite(&data, sizeof(unsigned char), (xsize * ysize), fp);
	unsigned char *wdata;
	wdata = new unsigned char[xsize * ysize];
	for(int y=0;y<ysize;y++){
	for(int x=0;x<xsize;x++){
		int j = GetPaletteNum(&(data[y * xsize + x]));
		if(j == -1)	continue;
		wdata[y * xsize + x] = (unsigned char)j;
	}
	}
	
	fwrite(wdata, sizeof(unsigned char), (xsize * ysize), fp);
	
	fclose(fp);
	return;
}



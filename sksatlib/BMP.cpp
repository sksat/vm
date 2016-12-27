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
					+ (xsize * ysize * COLOR_BIT_NUM);
	fh.bfReserved1		= 0;
	fh.bfReserved2		= 0;
	fh.bfOffBits		= 14 + 40;//sizeof(FileHeader) + sizeof(InfoHeader);
	
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
	ih.biClrUsed		= 256;
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
	
	fclose(fp);
	return;
}



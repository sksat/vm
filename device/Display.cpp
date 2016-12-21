#include "Display.h"

void Display::init(){
	scrnx = DEFAULT_SCRNX;
	scrny = DEFAULT_SCRNY;
	img = new unsigned char[scrnx * scrny * 3];	//横*縦*RGB
	
	init_palette();
}

Display::Display(uint8_t *vram){
	init();
	this->vram = vram;
}

Display::~Display(){
	delete[] img;
}

void Display::init_palette(){
	static unsigned char table_rgb[16 * 3] = {
		0x00, 0x00, 0x00,
		0xff, 0x00, 0x00,
		0x00, 0xff, 0x00,
		0xff, 0xff, 0x00,
		0x00, 0x00, 0xff,
		0xff, 0x00, 0xff,
		0x00, 0xff, 0xff,
		0xff, 0xff, 0xff,
		0xc6, 0xc6, 0xc6,
		0x84, 0x00, 0x00,
		0x00, 0x84, 0x00,
		0x84, 0x84, 0x00,
		0x00, 0x00, 0x84,
		0x84, 0x00, 0x84,
		0x00, 0x84, 0x84,
		0x84, 0x84, 0x84
	};
	
	for(int i=0; i<(16*3); i++){
		palette[i]	= table_rgb[i];
	}
}

unsigned char* Display::Draw(){
	/*
	//テスト描画
	unsigned int index=0;
	for(unsigned int i = 0; i<scrny; i++){
		int r = (i * 0xff) / scrny;
		for(unsigned int j = 0; j<scrnx; j++){
			img[index++] = r;
			img[index++] = (( j * 0xff) / scrnx);
			img[index++] = ~r;
		}
	}
	*/
	
	for(int x=0;x<scrnx;x++){
		for(int y=0;y<scrny;y++){
			int i=(y*scrnx + x)*3;
			char n = vram[y*scrnx + x];	//当該座標の色番号
			img[i]	= palette[n*3];	//色番号に対応したRGB
			img[i+1]= palette[n*3+1];	//green
			img[i+2]= palette[n*3+2];	//blue
		}
	}
	
	return img;
}

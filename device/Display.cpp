#include "Display.h"

void Display::init(){
	scrnx = DEFAULT_SCRNX;
	scrny = DEFAULT_SCRNY;
	img = new char[scrnx * scrny * 3];	//横*縦*RGB
}

Display::Display(uint8_t *vram){
	init();
	this->vram = vram;
}

Display::~Display(){
	delete[] img;
}

char* Display::Draw(){
	unsigned int index=0;
	for(unsigned int i = 0; i<scrny; i++){
		int r = (i * 0xff) / scrny;
		for(unsigned int j = 0; j<scrnx; j++){
//			img[index++] = r;
//			img[index++] = (( j * 0xff) / scrnx);
//			img[index++] = ~r;
		}
	}
	return img;
}

#include "Display.h"

void Display::init(){
	scrnx = DEFAULT_SCRNX;
	scrny = DEFAULT_SCRNY;
}

Display::Display(Gui *gui, uint8_t *vram){
	init();
	this->gui = gui;
	this->vram = vram;
}

Display::~Display(){
	
}



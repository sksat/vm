#include <stdio.h>

#include "Image.h"

namespace sksat {

void Image::init(){
	loadflg = false;
	data	= NULL;
	xsize	= 0;
	ysize	= 0;
}

Image::Image(){
	init();
}

Image::Image(unsigned int xsize, unsigned int ysize){
	init();
	ChangeSize(xsize, ysize);
}

Image::~Image(){
	if(data != NULL) delete data;
}

bool Image::LoadRGBA(unsigned char *addr, unsigned int xsize, unsigned int ysize){
	if(IsLoaded())	return false;
	if(xsize > this->xsize || ysize > this->ysize){
		return false;
	}
	
	for(int y=0;y<ysize;y++){
	for(int x=0;x<xsize;x++){
		for(int i=0;i<4;i++){
			data[(this->xsize*y + x)*4 + i] = addr[(this->xsize*y + x)*4 + i];
		}
	}
	}
	
	loadflg = true;
	return true;
}

bool Image::LoadRGB(unsigned char *addr, unsigned int xsize, unsigned int ysize){
	if(IsLoaded())	return false;
	if(xsize != this->xsize || ysize != this->ysize)	return false;
	
	for(int y=0;y<ysize;y++){
	for(int x=0;x<xsize;x++){
		for(int i=0;i<3;i++){
			data[(this->xsize*y + x)*4 + i] = addr[(this->xsize*y + x)*3 + i];
		}
	}
	}
	
	loadflg = true;
	return true;
}

bool Image::ChangeSize(unsigned int xsize, unsigned int ysize){
	if(this->xsize == 0 || this->ysize == 0 || data==NULL){
		data = new unsigned char[xsize*ysize*4];
		this->xsize = xsize;
		this->ysize = ysize;
	}
}

};	//namespace

#ifndef DISPLAY_H_
#define DISPLAY_H_

#define DEVICE

#include "Device.h"
//#include "../Gui.h"

#define DEFAULT_SCRNX	320
#define DEFAULT_SCRNY	200

class Display : public Device {
private:
//	Gui	*gui;
	unsigned char palette[0xff * 3];//パレット。256個の色をRGBで保存。
	
	uint8_t *vram;
public:
	unsigned char *img;
private:
	int scrnx, scrny;
	
	void init();
	void init_palette();
public:	
	Display(uint8_t *vram);
	~Display();
	
	unsigned char* Draw();
};

#endif //DISPLAY_H_


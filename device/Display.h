#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "Device.h"
//#include "../Gui.h"

#define DEFAULT_SCRNX	320
#define DEFAULT_SCRNY	200

class Display : public Device {
private:
//	Gui	*gui;
	uint8_t *vram;
	char *img;
	
	int scrnx, scrny;
	
	void init();
public:	
	Display(uint8_t *vram);
	~Display();
	
	char* Draw();
};

#endif //DISPLAY_H_


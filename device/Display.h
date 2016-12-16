#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "Device.h"
#include "../Gui.h"

class Display : public Device {
private:
	Gui	*gui;
	uint8_t *vram;
	
	int scrnx, scrny;
	
	void init();
public:
	Display(Gui *gui, uint8_t *vram);
	~Display();
};

#endif //DISPLAY_H_


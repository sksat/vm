#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "Device.h"

class Display : public Device {
private:
	uint8_t *vram;
	
	void init();
public:
	Display(uint8_t *vram);
};

#endif //DISPLAY_H_


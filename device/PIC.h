#ifndef PIC_H_
#define PIC_H_

#include "Device.h"

class PIC : public Device {
public:
	uint8_t out8(int port);
	void in8(int port, uint8_t data);
};

#endif

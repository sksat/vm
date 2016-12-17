#ifndef DEVICE_H_
#define DEVICE_H_

#include "../Emulator.h"

class Device {
private:
	
public:
	uint8_t out8(int port);	//IN命令の時に呼ばれる（デバイスからみたらOUTなので）。
				//あと、ひとつのデバイスで複数ポートあるかもしれないから引数にポートをとる
	void in8(int port, uint8_t data);
};

#ifndef DEVICE
	#include "Display.h"	
#endif

#endif //DEVICE_H_


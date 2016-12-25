#ifndef PPM_H_
#define PPM_H_

#include "Image.h"

namespace sksat {

class PPM : public Image {
private:
	int type;
public:
	PPM();
	~PPM();
	
	void Load(unsigned char *addr, int xsize, int ysize){ LoadRGB(addr,xsize,ysize); }

	void Read(const char *fname);
	void Write(const char *fname);
};

};

#endif

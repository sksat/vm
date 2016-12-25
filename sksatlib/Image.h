#ifndef IMAGE_H_
#define IMAGE_H_

namespace sksat {

//画像基底クラス
class Image {
protected:
	bool loadflg;
	unsigned int xsize, ysize;
	unsigned char *data;
private:
	void init();
public:
	Image();
	Image(unsigned int xsize, unsigned int ysize);
	~Image();

	bool ChangeSize(unsigned int xsize, unsigned ysize);

	bool LoadRGBA(unsigned char *addr, unsigned int xsize, unsigned int ysize);
	bool LoadRGB(unsigned char *addr, unsigned int xsize, unsigned int ysize);
	bool LoadBGR(unsigned char *addr, unsigned int xsize, unsigned int ysize);

	bool IsLoaded(){ return loadflg; }
};

};

#endif

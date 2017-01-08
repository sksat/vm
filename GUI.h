#ifndef GUI_H_
#define GUI_H_

#include <thread>
//#include <GL/freeglut.h>
#include "GL/freeglut.h"

#include "device/Display.h"

#define DEFAULT_SCRNX	320
#define DEFAULT_SCRNY	200

class GUI{
private:
	std::thread *hThread;
	int hMainWin;
	Display *disp;
	unsigned char *img;
	
	bool msgflg;
	
	int scrnx, scrny;
	
	void init();
	void ThreadProc();
	void display();
//	void timer(int val);
public:
	GUI();
	GUI(unsigned char *img);
	GUI(Display *disp);
	~GUI();
	
	void OpenWindow();
	void ChangeDisplay(Display *disp);
	void ChangeImgAddr(unsigned char *img);
};

#endif //GUI_H_

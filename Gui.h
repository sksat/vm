#ifndef GUI_H_
#define GUI_H_

#include <thread>
#include <GL/freeglut.h>

#define DEFAULT_SCRNX	320
#define DEFAULT_SCRNY	200

class Gui{
private:
	std::thread *hThread;
	
	int scrnx, scrny;
	
	void init();
	void ThreadProc();
	void display();
public:
	Gui();
	~Gui();
	
	void OpenWindow();
};

#endif //GUI_H_

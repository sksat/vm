#include <iostream>
#include "GUI.h"

using namespace std;

unsigned char *img;

typedef struct{
	unsigned char red, green, blue;
}Color;

void boxfill(Color *c, int x0, int y0, int x1, int y1){
	int x,y, i;
	for(y=y0;y<=y1;y++){
		for(x=x0;x<=x1;x++){
			i = (y*320+x)*3;
			img[i]	= c->red;
			img[i+1]	= c->green;
			img[i+2]	= c->blue;
		}
	}
}

void Gui::ThreadProc(){
	img = new unsigned char[scrnx * scrny *3];
	Color c;
	c.red = 0xff;
	c.green = 0x00;
	c.blue = 0x00;
	boxfill(&c, 20, 20, 150, 100);
	
//cout<<"a"<<endl;	
	int argc=1;
	char *argv = new char[1];
	glutInit(&argc, &argv);		//fake command-line args
	
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(scrnx, scrny);
	
	hMainWin = glutCreateWindow("display");
	
//	gluOrtho2D(0.0, scrnx, 0.0, scrny);
	glPixelZoom(1,-1);
	
	//glutDisplayFunc(a::display);	//message loopをglutMainLoopではなくwhileでやっていて、その中でdisplayを呼んでいるため必要ない（こうするためにはGui::displayをstaticメンバ関数にする必要がある）
	
	while(msgflg){	//message loop
		glutMainLoopEvent();
		this->display();
	}

	glutDestroyWindow(hMainWin);
	cout<<"destroy"<<endl;
}

void Gui::display(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2f(-1,1);
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glDrawPixels(scrnx, scrny, GL_RGB, GL_UNSIGNED_BYTE, disp->Draw());
//	glMatrixMode(GL_MODELVIEW);
	glFlush();
}

void Gui::init(){
	disp = NULL;
	scrnx = DEFAULT_SCRNX;
	scrny = DEFAULT_SCRNY;
	msgflg = true;
}

Gui::Gui(){
	init();
}

Gui::Gui(Display *disp){
	init();
	ChangeDisplay(disp);
}

Gui::~Gui(){
	msgflg = false;
	hThread->detach();
	delete hThread;
	delete img;
}

void Gui::OpenWindow(){
	hThread = new thread(&Gui::ThreadProc, this);	//メンバ関数を指定する場合は第２引数=this
	
//	hThread->join();	//とりあえず終わるまで待つ
}

void Gui::ChangeDisplay(Display *disp){
	if(disp == NULL) return;
	this->disp = disp;	//描画スレッドのほうで不整合が起きるのは今は気にしない
}



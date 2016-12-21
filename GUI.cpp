#include <iostream>
#include "GUI.h"

using namespace std;

unsigned char *img;

void GUI::ThreadProc(){
	img = new unsigned char[scrnx * scrny *3];
		
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

void GUI::display(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2f(-1,1);
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glDrawPixels(scrnx, scrny, GL_RGB, GL_UNSIGNED_BYTE, disp->Draw());
//	glMatrixMode(GL_MODELVIEW);
	glFlush();
}

void GUI::init(){
	disp = NULL;
	scrnx = DEFAULT_SCRNX;
	scrny = DEFAULT_SCRNY;
	msgflg = true;
}

GUI::GUI(){
	init();
}

GUI::GUI(Display *disp){
	init();
	ChangeDisplay(disp);
}

GUI::~GUI(){
	msgflg = false;
	hThread->detach();
	delete hThread;
	delete img;
}

void GUI::OpenWindow(){
	hThread = new thread(&GUI::ThreadProc, this);	//メンバ関数を指定する場合は第２引数=this
	
//	hThread->join();	//とりあえず終わるまで待つ
}

void GUI::ChangeDisplay(Display *disp){
	if(disp == NULL) return;
	this->disp = disp;	//描画スレッドのほうで不整合が起きるのは今は気にしない
}



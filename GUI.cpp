#include <iostream>
#include "Gui.h"

using namespace std;

unsigned char *img;// = new unsigned char[320*200*3];

void Gui::ThreadProc(){
	img = new unsigned char[scrnx * scrny *3];
	int index=0;
	for(int x=0;x<scrnx;x++){
		for(int y=0;y<scrny;y++){
			img[scrnx*y+x] = 0xff;
		}
	}
//cout<<"a"<<endl;	
	int argc;
	char *argv = new char[1];
	glutInit(&argc, &argv);		//fake command-line args
	
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(scrnx, scrny);
	
	hMainWin = glutCreateWindow("display");
	
//	glutDisplayFunc(display);	//message loopをglutMainLoopではなくwhileでやっていて、その中でdisplayを呼んでいるため必要ない（こうするためにはGui::displayをstaticメンバ関数にする必要がある）
	
	while(msgflg){	//message loop
//cout<<"msg loop"<<endl;
		glutMainLoopEvent();
		this->display();
		glDrawPixels(scrnx, scrny, GL_RGB, GL_UNSIGNED_BYTE, img);
		glFlush();
	}

//	glutDestroyWindow(hMainWin);
	cout<<"destroy"<<endl;
}

void Gui::display(){
//cout<<"d";
	glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2f(-1,1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//	glDrawPixels(scrnx, scrny, GL_RGB, GL_UNSIGNED_BYTE, img);//disp->Draw());
//	glFlush();
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



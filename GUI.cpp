#include <iostream>
#include "GUI.h"

using namespace std;

//typedef void (GUI::*GUIFunc_i)(int);

void test(int val){
	cout<<"test "<<val<<endl;
}

void GUI::ThreadProc(){
//	img = new unsigned char[scrnx * scrny *3];
		
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
//	GUIFunc_i f = timer;
//	glutTimerFunc(500, f, 0);
	
	int menu = glutCreateMenu(test);
	glutAddMenuEntry("menu1", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	while(msgflg){	//message loop
		glutMainLoopEvent();
		this->display();
	}

	glutDestroyWindow(hMainWin);
	cout<<"destroy"<<endl;
}

void GUI::display(){
	if(disp != NULL){
		img = disp->Draw();
	}
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2f(-1,1);
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	if(img != NULL){
		glDrawPixels(scrnx, scrny, GL_RGB, GL_UNSIGNED_BYTE, img);
	}
//	glMatrixMode(GL_MODELVIEW);
	glFlush();
}

/*
void GUI::timer(int val){
	glutPostRedisplay();
}
*/

void GUI::init(){
	disp = NULL;
	img = NULL;
	scrnx = DEFAULT_SCRNX;
	scrny = DEFAULT_SCRNY;
	msgflg = true;
}

GUI::GUI(){
	init();
}

GUI::GUI(unsigned char *img){
	init();
	ChangeImgAddr(img);
}


GUI::GUI(Display *disp){
	init();
	ChangeDisplay(disp);
}


GUI::~GUI(){
	msgflg = false;
	hThread->detach();
	delete hThread;
//	delete img;
}

void GUI::OpenWindow(){
	hThread = new thread(&GUI::ThreadProc, this);	//メンバ関数を指定する場合は第２引数=this
	
//	hThread->join();	//とりあえず終わるまで待つ
}

void GUI::ChangeImgAddr(unsigned char *img){
	if(img == NULL)
		return;
	this->img = img;
}


void GUI::ChangeDisplay(Display *disp){
	if(disp == NULL) return;
	this->disp = disp;	//描画スレッドのほうで不整合が起きるのは今は気にしない
	ChangeImgAddr(disp->img);
}




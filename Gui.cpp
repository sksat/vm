#include "Gui.h"

using namespace std;

void Gui::ThreadProc(){
	int argc;
	char *argv = new char[1];
	glutInit(&argc, &argv);		//fake command-line args
	
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(scrnx, scrny);
	
	glutCreateWindow("display");
	
//	glutDisplayFunc(display);	//message loopをglutMainLoopではなくwhileでやっていて、その中でdisplayを呼んでいるため必要ない（こうするためにはGui::displayをstaticメンバ関数にする必要がある）
	
	while(true){	//message loop
		glutMainLoopEvent();
		this->display();
	}
}

void Gui::display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void Gui::init(){
	scrnx = DEFAULT_SCRNX;
	scrny = DEFAULT_SCRNY;
}

Gui::Gui(){
	init();
}

Gui::~Gui(){
	
}

void Gui::OpenWindow(){
	hThread = new thread(&Gui::ThreadProc, this);	//メンバ関数を指定する場合は第２引数=this
	
	hThread->join();	//とりあえず終わるまで待つ
}

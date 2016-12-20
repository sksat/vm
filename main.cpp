#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "Emulator.h"
#include "GUI.h"
#include "device/Device.h"

#define DEBUG

#ifdef DEBUG
#undef DEBUG
#define DEBUG(m) cout<<m<<endl;
#else
#define DEBUG(m)
#endif

using namespace std;

Emulator	*emu;
Gui		*gui;
Display		*disp;

void boxfill(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1){
	for(int y=y0; y<=y1; y++){
		for(int x=x0; x<=x1; x++){
			vram[y * xsize + x] = c;
		}
	}
	return;
}

int main(int argc, char **argv){
	
	//TODO parse args
	
	emu = new Emulator();
	cout<<"emulator created."<<endl;
	
	disp = new Display(emu->memory + VRAM_ADDR);
	gui = new Gui(disp);
	
//	getchar();
	
	emu->LoadBinary(argv[1], 0x7c00, 512);
	
	emu->EIP = 0x7c00;
//	emu->EAX = 0xffffffff;
	
	//internal boxfill
	boxfill(emu->memory + VRAM_ADDR, 320, 2, 20, 20, 120, 120);
	
	gui->OpenWindow();
	
	//emulation
	while(true){
		int bit		= emu->GetBitMode();
		uint8_t code	= emu->GetCode8(0);
		instruction_func_t* func;
		
		cout<<"emu: ";
		cout<<"EIP = "<<hex<<showbase<<emu->EIP<<", ";
		cout<<"Code = "<<(uint32_t)code<<endl;
		
		if(bit == 16){
			func = instructions16[code];
		}else if(bit == 32){
			func = instructions32[code];
		}else if(bit == 64){
			cout<<"64bitには対応していません。"<<endl;
			break;
		}
		
		if(func == NULL){
			cout<<"命令("<<showbase<<(int)code<<")は実装されていません。"<<endl;
			break;
		}
		
		//execute
		func(emu);
		
		if(emu->EIP > emu->GetMemSize()){
			cout<<"out of memory."<<endl;
			break;
		}
		
//		emu->EIP.reg32++;
	}
	
	emu->DumpRegisters(32);
	emu->DumpMemory("memdump.bin");
	
	delete emu;
	cout<<"emulator deleted."<<endl;
	
	delete gui;
	delete disp;
	return 0;
}



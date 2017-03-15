#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "Emulator.h"
#include "GUI.h"
#include "device/Device.h"

#define DEBUG

//#define QUIET

#define INTERNAL_BOXFILL
//#define TEST_VRAM
#define HARIBOTE_UI

using namespace std;

Emulator	*emu;
GUI		*gui;
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
	gui = new GUI(disp);
	
//	getchar();
	
	emu->LoadBinary(argv[1], 0x7c00, 512);
	
	emu->EIP = 0x7c00;	//EIP初期設定
	emu->ESP = 0x7c00;
	
	//internal boxfill
#ifdef INTERNAL_BOXFILL

#ifdef TEST_VRAM
	for(int i=VRAM_ADDR; i<=0xaffff; i++){
		char *p;
		p = (char*)(i + emu->memory);
		*p = i & 0x0f;
	}
#endif

#ifdef HARIBOTE_UI
	boxfill(emu->memory + VRAM_ADDR, 320, 14, 0,      0, 320-1, 200-29);
	boxfill(emu->memory + VRAM_ADDR, 320,  8, 0, 200-28, 320-1, 200-28);
	boxfill(emu->memory + VRAM_ADDR, 320,  7, 0, 200-27, 320-1, 200-27);
	boxfill(emu->memory + VRAM_ADDR, 320,  8, 0, 200-26, 320-1, 200- 1);
	
	boxfill(emu->memory + VRAM_ADDR, 320,  7,  3, 200-24, 59, 200-24);
	boxfill(emu->memory + VRAM_ADDR, 320,  7,  2, 200-14,  2, 200- 4);
	boxfill(emu->memory + VRAM_ADDR, 320, 15,  3, 200- 4, 59, 200- 4);
	boxfill(emu->memory + VRAM_ADDR, 320, 15, 59, 200-23, 59, 200- 5);
	boxfill(emu->memory + VRAM_ADDR, 320,  0,  2, 200- 3, 59, 200- 3);
	boxfill(emu->memory + VRAM_ADDR, 320,  0, 60, 200-24, 60, 200- 3);
	
	boxfill(emu->memory + VRAM_ADDR, 320, 15, 320-47, 200-24, 320- 4, 200-24);
	boxfill(emu->memory + VRAM_ADDR, 320, 15, 320-47, 200-23, 320-47, 200- 4);
	boxfill(emu->memory + VRAM_ADDR, 320,  7, 320-47, 200- 3, 320- 4, 200- 3);
	boxfill(emu->memory + VRAM_ADDR, 320,  7, 320- 3, 200-24, 320- 3, 200- 3);
#endif //haribote-ui

#endif //internal boxfill
	
	gui->OpenWindow();
	
//	emu->ESP = 0xffff;
//	emu->DumpRegisters(32);
	//emulation
	while(true){
		int bit		= emu->GetBitMode();
		uint8_t code	= emu->GetCode8(0);
		instruction_func_t* func;

#ifndef QUIET
		cout<<"emu: ";
		cout<<"EIP = "<<hex<<showbase<<emu->EIP<<", ";
		cout<<"Code = "<<(uint32_t)code<<endl;
#endif

		if(bit == 16){
			func = instructions16[code];
		}else if(bit == 32){
			func = instructions32[code];
		}else if(bit == 64){
			cout<<"64bitには対応していません。"<<endl;
			break;
		}
		
		if(func == NULL){
//			cout<<"命令("<<showbase<<(int)code<<")は実装されていません。"<<endl;
			// おふざけ
			cout<<showbase<<(int)code<<"...？知らない命令ですね。"<<endl;
			break;
		}
		
		//execute
		func(emu);
		
		if(emu->EIP == 0){
			cout<<"EIP = 0になったので終了"<<endl;
			break;
		}
		
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



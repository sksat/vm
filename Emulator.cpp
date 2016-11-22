#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>
#include <sstream>
#include "Emulator.h"

using namespace std;

const char* registers_name16[] = { "AX",  "CX",  "DX",  "BX",  "SP",  "BP",  "SI",  "DI"};
const char* registers_name32[] = {"EAX", "ECX", "EDX", "EBX", "ESP", "EBP", "ESI", "EDI"};


//void test(Emulator *emu){
//	cout<<"test("<<emu<<")"<<endl;
//}

Emulator::Emulator(){
	BitMode = DEFAULT_BIT_MODE;
	memory_size = DEFAULT_MEMORY_SIZE;
	memory = new (nothrow) uint8_t[memory_size];
	if(memory == NULL){
		cout<<"error new."<<endl;
	}
	
	InitInstructions16();
	InitInstructions32();
	
//	memset(memory, 0x01, memory_size);
//	test(this);
}

Emulator::~Emulator(){
	delete[] memory;
}


int Emulator::GetBitMode(){
	return BitMode;
}

//IsReal is defined in header.

bool Emulator::IsProtected(){
	if((CR[0].reg32 & 0x80000000) == 0){	//最上位ビットが0だったらリアルモード
		return false;
	}
	return true;
}

void Emulator::LoadBinary(const char* fname, uint32_t addr, int size){
	FILE *fp;
	fp = fopen(fname, "rb");
	if(fp == NULL){
		return;
	}
	fread(memory + addr, 1, size, fp);
	fclose(fp);
}

uint8_t Emulator::GetCode8(int index){
	if(memory_size < (EIP +index))
		return 0xff;
	return memory[EIP + index];
}

void Emulator::DumpRegisters(int bit){
	cout<<"---Dump Registers---"<<endl;
	
	switch(bit){
	case 16:
		for(int i=0; i<REGISTERS_COUNT; i++){
			cout<<registers_name16[i]<<" = ";
			cout<<hex<<showbase<<reg[i].reg16;
			cout<<endl;
		}
		cout<<"IP = "<<IP<<endl;
		cout<<"FLAGS = "<<FLAGS<<endl;
		break;
	case 32:
		for(int i=0; i<REGISTERS_COUNT; i++){
			cout<<registers_name32[i]<<" = ";
			cout<<hex<<showbase<<reg[i].reg32;
			cout<<endl;
		}
		cout<<"EIP = "<<EIP<<endl;
		cout<<"EFLAGS = "<<EFLAGS<<endl;
		for(int i=0; i<4; i++){
			cout<<"CR"<<dec<<i<<" = ";
			cout<<hex<<showbase<<CR[i].reg32<<endl;
		}
		break;
	//case 64:
	//	break;
	default:
		break;
	}
	
	cout<<"--------------------"<<endl;
	
	return;
}

void Emulator::DumpRegisters(){
	int bit = GetBitMode();
	DumpRegisters(bit);
	return;
}

void Emulator::DumpMemory(const char *fname, uint8_t addr, uint8_t size){
	if(memory_size < addr)
		return;
	if(memory_size < addr+size){
		size = memory_size - addr;
	}
	
	FILE *fp;
	fp = fopen(fname, "wb");
	fwrite(memory+addr, size, 1, fp);
	fclose(fp);
}




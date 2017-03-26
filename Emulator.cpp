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
	
	InitRegisters();
	
	InitInstructions16();
	InitInstructions32();
	
//	memset(memory, 0x01, memory_size);
//	test(this);
}

Emulator::~Emulator(){
	delete[] memory;
}

//各レジスタの初期化
void Emulator::InitRegisters(){
	GDTR.base_addr	= 0;
	GDTR.table_limit= 0xffff;	// GDTRの初期値はIntel*3巻2.4.1参照
	IDTR.base_addr	= 0;
	IDTR.table_limit= 0xffff;	// 同上2.4.3
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
	if(memory_size < (EIP +index)){
		cout<<"error"<<endl;
		return 0xff;
	}
	return memory[EIP + index];
}

int8_t Emulator::GetSignCode8(int index){
	return (int8_t)GetCode8(index);
}

uint32_t Emulator::GetCode32(int index){
	uint32_t ret = 0;
	
	//リトルエンディアンでメモリの値を取得
	for(int i=0; i<4; i++){
		ret |= GetCode8(index + i) << (i * 8);
	}
	
	return ret;
}

int32_t Emulator::GetSignCode32(int index){
	return (int32_t)GetCode32(index);
}

uint8_t Emulator::GetRegister8(int index){
	if(index < 4){
		return reg[index].high8;
	}else{
		return reg[index - 4].low8;
	}
}

uint32_t Emulator::GetRegister32(int index){
	return reg[index].reg32;
}

void Emulator::SetRegister8(int index, uint8_t val){
	if(index < 4){
		uint32_t r = reg[index].reg32 & 0xffffff00;
		reg[index].reg32 = r | (uint32_t)val;
	}else if(index <= REGISTERS_COUNT32){
		uint32_t r = reg[index - 4].reg32 & 0xffff00ff;
		reg[index - 4].reg32 = r | ((int32_t)val << 8);
	}else{
		cout<<index<<"番目のレジスタとかなんですか"<<endl;
	}
}

void Emulator::SetRegister32(int index, uint32_t val){
	reg[index].reg32 = val;
}

uint32_t Emulator::GetMemory8(uint32_t addr){
	if(addr > memory_size){
		cout<<"fatal error:"<<"メモリサイズを超えたアドレス"<<addr<<"を参照しようとしました。"<<endl;
		return 0x00;
	}
	return memory[addr];
}

uint32_t Emulator::GetMemory32(uint32_t addr){
	// little endian
	uint32_t ret = 0;
	for(int i=0; i<4; i++){
		ret |= GetMemory8(addr + i) << (8 * i);
	}
	
	return ret;
}

void Emulator::SetMemory8(uint32_t addr, uint32_t val){
	if(addr > memory_size){
		cout<<"fatal error:"<<"メモリサイズを超えたアドレス"<<addr<<"に値("<<(val & 0xff)<<")をセットしようとしました"<<endl;
		return;
	}
//	cout<<addr<<"への書き込み("<<(val&0xff)<<endl;
	memory[addr] = val & 0xFF;
	return;
}

void Emulator::SetMemory32(uint32_t addr, uint32_t val){
	//little endian
	for(int i=0; i<4; i++){
		SetMemory8(addr + i, val >> (i*8));
	}

	return;
}

void Emulator::Push32(uint32_t val){
//	uint32_t addr = /*GetRegister32(ESP)*/ ESP  - 4;
//	SetRegister32(ESP, addr);
//	ESP = addr;
	ESP = ESP - 4;
	SetMemory32(ESP, val);
}

uint32_t Emulator::Pop32(){
	uint32_t addr = ESP;//GetRegister32(ESP);
	uint32_t ret = GetMemory32(addr);
//	SetRegister32(ESP, addr + 4);
	ESP = addr + 4;
	return ret;
}

void Emulator::SetCarry(int is_carry){
	if(is_carry){
		EFLAGS != CARRY_FLAG;
	}else{
		EFLAGS &= ~CARRY_FLAG;
	}
}

void Emulator::SetZero(int is_zero){
	if(is_zero){
		EFLAGS |= ZERO_FLAG;
	}else{
		EFLAGS &= ~ZERO_FLAG;
	}
}

void Emulator::SetSign(int is_sign){
	if(is_sign){
		EFLAGS |= SIGN_FLAG;
	}else{
		EFLAGS &= ~SIGN_FLAG;
	}
}

void Emulator::SetOverflow(int is_overflow){
	if(is_overflow){
		EFLAGS |= OVERFLOW_FLAG;
	}else{
		EFLAGS &= ~OVERFLOW_FLAG;
	}
}

void Emulator::UpdateEflagsSub(uint32_t v1, uint32_t v2, uint64_t result){
	// 各値の符号取得
	int sign1 = v1 >> 31;
	int sign2 = v2 >> 31;
	int signr = (result >> 31) & 1;

	// carry
	SetCarry(result >> 32);
	// zero
	SetZero(result == 0);
	// sign
	SetSign(signr);
	// overflow
	SetOverflow(sign1 != sign2 && sign1 != signr);
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

void Emulator::DumpMemory(const char *fname, uint32_t addr, uint32_t size){
	if(memory_size < addr)
		return;
	if(memory_size < addr+size){
		size = memory_size - addr;
	}
	
	FILE *fp;
	fp = fopen(fname, "wb");
	fwrite(memory+addr, sizeof(char), size, fp);
	fclose(fp);
}




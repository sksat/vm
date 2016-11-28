#include <iostream>

#include "Emulator.h"

instruction_func_t* instructions32[256];

namespace instruction32{

void mov_r8_imm8(Emulator *emu){
	uint8_t reg = emu->GetCode8(0) - 0xB0;
	emu->reg[reg].reg32 = emu->GetCode8(1);
	emu->EIP += 2;
//	std::cout<<"a";
}

void mov_r32_imm32(Emulator *emu){
	uint8_t reg	= emu->GetCode8(0) - 0xB8;
	uint32_t val	= emu->GetCode8(1);
	emu->reg[reg].reg32 = val;
	emu->EIP += 5;
}

}



using namespace instruction32;

void InitInstructions32(void){
	int i;
	instruction_func_t** func = instructions32;
	
	//func[0x10]	= add_rm32_r32;
	
	//func[0x3B]	= cmp_r32_rm32;
	//func[0x3C]	= cmp_al_imm8;
	//func[0x3D]	= cmp_eax_imm32;
	
	/*
	for(i=0;i<8;i++){
		func[0x40 + i]	= inc_r32;
	}
	*/
	
	/*
	for(i=0;i<8;i++){
		func[0x50 + i]	= push_r32;
	}
	*/
	
	/*
	for(i=0;i<8;i++){
		func[0x58 + i]	= pop_r32;
	}
	*/
	
	
	//func[0x68]	= push_imm32;
	//func[0x6A]	= push_imm8;
	
	//func[0x70]	= jo;
	//func[0x71]	= jno;
	//func[0x72]	= jc;
	//func[0x73]	= jnc;
	//func[0x74]	= jz;
	//func[0x75]	= jnz;
	//func[0x78]	= js;
	//func[0x79]	= jl;
	//func[0x7C]	= jle;
	
	//func[0x83]	= code_83;
	//func[0x88]	= mov_rm8_r8;
	//func[0x89]	= mov_rm32_r32;
	//func[0x8A]	= mov_r8_rm8;
	//func[0xBB]	= mov_r32_rm32;
	
	for(i=0;i<8;i++){
		func[0xB0 + i]	= mov_r8_imm8;
	}
	
	for(i=0;i<8;i++){
		func[0xB8 + i]	= mov_r32_imm32;
	}
}



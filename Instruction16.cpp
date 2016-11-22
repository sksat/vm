#include "Emulator.h"

instruction_func_t* instructions16[256];

namespace instruction16{

void test(Emulator *emu){
	
}

void mov_r8_imm8(Emulator *emu){
	uint8_t reg = emu->GetCode8(0) - 0xB0;
	emu->reg[reg].reg16 = emu->GetCode8(1);
	emu->EIP += 2;
}

}

using namespace instruction16;

void InitInstructions16(){
	int i;
	instruction_func_t** func = instructions16;
	
//	func[0x00] = test;
	
	for(i=0;i<8;i++){
		func[0xB8 + i] = mov_r8_imm8;
	}
}



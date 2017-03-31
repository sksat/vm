#include "Emulator.h"

instruction_func_t* instructions16[256];

namespace instruction16{

void add_rm16_r16(Emulator *emu){
	
}

void test(Emulator *emu){
	
}


}

using namespace instruction16;

void InitInstructions16(){
	int i;
	instruction_func_t** func = instructions16;
	
//	func[0x00] = test;
	
}



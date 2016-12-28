#include <iostream>

#include "ModRM.h"

using namespace std;

ModRM::ModRM(){
	
}

ModRM::ModRM(Emulator *emu){
	this->emu = emu;
	Parse(emu);
}

void ModRM::Parse(Emulator *emu){
	uint8_t code = emu->GetCode8(0);
	Mod	= ((code & 0xC0) >> 6);
	opecode	= ((code & 0x38) >> 3);
	RM	= code & 0x07;

	emu->EIP++;

	if(Mod != 3 && RM == 4){
		SIB = emu->GetCode8(0);
		emu->EIP++;
	}

	if((Mod == 0 && RM == 5) || Mod == 2){
		disp32	= emu->GetSignCode32(0);
		emu->EIP += 4;
	}else if(Mod == 1){
		disp8 = emu->GetSignCode8(0);
		emu->EIP++;
	}

	return;
}

void ModRM::Parse(){
	if(emu != NULL)
		Parse(emu);
}

uint32_t ModRM::GetRM32(Emulator *emu){
	if(Mod == 3){
		return emu->GetRegister32(RM);
	}else{
		uint32_t addr = CalcMemAddr(emu);
		return emu->GetMemory32(addr);
	}
}

uint32_t ModRM::GetRM32(){
	
}

void ModRM::SetRM32(Emulator *emu, uint32_t val){
	if(Mod == 3){
		emu->SetRegister32(RM, val);
	}else{
		uint32_t addr = CalcMemAddr(emu);
		emu->SetMemory32(addr, val);
	}
}

void ModRM::SetRM32(uint32_t val){
	if(emu != NULL)
		SetRM32(emu, val);
}

uint32_t ModRM::CalcMemAddr(Emulator *emu){
	if(Mod == 0){
		if(RM == 4){
			cout<<"not implemented ModRM Mod = 0, RM = 4"<<endl;
			return 0;
		}else if(RM == 5){
			return disp32;
		}else{
			return emu->GetRegister32(RM);
		}
	}else if(Mod == 1){
		if(RM == 4){
			cout<<"not implemented ModRM Mod = 1, RM = 4"<<endl;
			return 0;
		}else{
			return emu->GetRegister32(RM) + disp8;
		}
	}else if(Mod == 2){
		if(RM == 4){
			cout<<"not implemented ModRM Mod = 2, RM = 4"<<endl;
			return 0;
		}else{
			return emu->GetRegister32(RM) + disp32;
		}
	}else{
		cout<<"not implemented ModRM Mod = 3"<<endl;
		return 0;
	}
}

uint32_t ModRM::CalcMemAddr(){
	if(emu == NULL)
		return 0;

	return CalcMemAddr(emu);
}

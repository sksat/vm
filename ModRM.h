#ifndef MODRM_H_
#define MODRM_H_

#include "Emulator.h"

class ModRM {
private:
	Emulator *emu;
public:
	uint8_t Mod;
	union {
		uint8_t opecode;
		uint8_t reg_index;
	};
	uint8_t RM;
	uint8_t SIB;
	union {
		int8_t disp8;
		uint32_t disp32;
	};
public:
	ModRM();
	ModRM(Emulator *emu);
	~ModRM();

	void Parse(Emulator *emu);
	void Parse();
	uint32_t GetRM32(Emulator *emu);
	uint32_t GetRM32();
	void SetRM32(Emulator *emu, uint32_t val);
	void SetRM32(uint32_t val);
	uint32_t CalcMemAddr(Emulator *emu);
	uint32_t CalcMemAddr();
};

#endif //MODRM_H_


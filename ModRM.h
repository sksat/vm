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
//	~ModRM();

	void Parse(Emulator *emu);
	void Parse();

	uint8_t GetRM8(Emulator *emu);
	uint8_t GetRM8();
	void SetRM8(Emulator *emu, uint8_t val);
	void SetRM8(uint8_t val);

	uint32_t GetRM32(Emulator *emu);
	uint32_t GetRM32();
	void SetRM32(Emulator *emu, uint32_t val);
	void SetRM32(uint32_t val);

	uint8_t GetR8(Emulator *emu);
	uint8_t GetR8();
	void SetR8(Emulator *emu, uint8_t val);
	void SetR8(uint8_t val);

	uint32_t GetR32(Emulator *emu);
	uint32_t GetR32();
	void SetR32(Emulator *emu, uint32_t val);
	void SetR32(uint32_t val);

	uint32_t CalcMemAddr(Emulator *emu);
	uint32_t CalcMemAddr();
};

#endif //MODRM_H_


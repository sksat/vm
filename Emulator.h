#ifndef EMULATOR_H_
#define EMULATOR_H_

#include <stdio.h>
#include <stdint.h>

#define DEFAULT_BIT_MODE	32//16
#define DEFAULT_MEMORY_SIZE	(1024 * 1024)	//1MB
#define REGISTERS_COUNT		8

extern const char* registers_name16[];
extern const char* registers_name32[];

typedef union {
	uint32_t reg32;
	uint16_t reg16;
	struct {
		uint8_t low8;
		uint8_t high8;
	};
} Register;	// 32bit register

#define EAX	reg[0].reg32

#define FLAGS	eflags.reg16
#define EFLAGS	eflags.reg32
#define IP	eip.reg16
#define EIP	eip.reg32

class Emulator{
private:
	int BitMode;
	int memory_size;
public:
	Register CR[5];		// CR0 ~ CR4 register
	Register eflags;
	
	Register eip;
	
	Register reg[REGISTERS_COUNT];
	
	uint8_t *memory;
public:				// member funcs
	Emulator();
	~Emulator();
	
	int GetBitMode();
	bool IsReal(){	return !IsProtected();	}
	bool IsProtected();
	size_t GetMemSize(){	return memory_size;	}
	
	void LoadBinary(const char* fname, uint32_t addr, int size);
	
	uint8_t GetCode8(int index);
	int8_t  GetSignCode8(int index);
	uint32_t GetCode32(int index);
	
	void DumpRegisters(int bit);
	void DumpRegisters();
	void DumpMemory(const char *fname, uint8_t addr, uint8_t size);
	void DumpMemory(const char *fname, uint8_t size){	DumpMemory(fname, 0x00, size);	}
	void DumpMemory(const char *fname){	DumpMemory(fname, memory_size);	}
};

//instructions

typedef void instruction_func_t(Emulator*);

void InitInstructions16(void);
void InitInstructions32(void);

extern instruction_func_t* instructions16[256];
extern instruction_func_t* instructions32[256];

#endif //EMULATOR_H_

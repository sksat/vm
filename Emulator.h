#ifndef EMULATOR_H_
#define EMULATOR_H_

#include <stdio.h>
#include <stdint.h>

#define DEFAULT_BIT_MODE	32//16		//デフォルトの起動時のビット。本来は16。
#define DEFAULT_MEMORY_SIZE	(1024 * 1024)	//デフォルトのメモリサイズ。1MB
#define REGISTERS_COUNT		8		//レジスタの本数(16/32bit)

#define VRAM_ADDR		0xa0000

#define LOW			0
#define HIGH			1

extern const char* registers_name16[];		//16bitレジスタの名前
extern const char* registers_name32[];		//32bitレジスタの名前

//32bitレジスタ型
typedef union {
	uint32_t reg32;
	uint16_t reg16;
	struct {
		uint8_t low8;
		uint8_t high8;
	};
} Register;	// 32bit register

//16bitレジスタに簡単にアクセスするためのdefine
#define  AX	reg[0].reg16
#define  CX	reg[1].reg16
#define  DX	reg[2].reg16
#define  BX	reg[3].reg16
#define  SP	reg[4].reg16
#define  BP	reg[5].reg16
#define  SI	reg[6].reg16
#define  DI	reg[7].reg16

//32bitレジスタに簡単にアクセスするためのdefine
#define EAX	reg[0].reg32
#define ECX	reg[1].reg32
#define EDX	reg[2].reg32
#define EBX	reg[3].reg32
#define ESP	reg[4].reg32
#define EBP	reg[5].reg32
#define ESI	reg[6].reg32
#define EDI	reg[7].reg32

//特殊なレジスタに簡単にアクセスするためのdefine
#define FLAGS	eflags.reg16
#define EFLAGS	eflags.reg32
#define IP	eip.reg16
#define EIP	eip.reg32

//セグメントレジスタ忘れてた

//エミュレータクラス
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
	
	void LoadBinary(const char* fname, uint32_t addr, int size);	//バイナリファイルを読み込んでメモリの指定番地に指定サイズだけ転送する
	
	uint8_t GetCode8(int index);
	int8_t  GetSignCode8(int index);
	uint32_t GetCode32(int index);
	int32_t GetSignCode32(int index);

	uint8_t GetRegister8(int index);
	uint32_t GetRegister32(int index);

	void SetRegister8(int index, uint8_t val);
	void SetRegister32(int index, uint32_t val);

	uint32_t GetMemory8(uint32_t addr);
	uint32_t GetMemory32(uint32_t addr);
	void SetMemory8(uint32_t addr, uint32_t val);
	void SetMemory32(uint32_t addr, uint32_t val);

	void DumpRegisters(int bit);		//各レジスタの値を標準入出力に書き込む。引数はビットモード。
	void DumpRegisters();
	void DumpMemory(const char *fname, uint8_t addr, uint8_t size);
	void DumpMemory(const char *fname, uint8_t size){	DumpMemory(fname, 0x00, size);	}
	void DumpMemory(const char *fname){	DumpMemory(fname, memory_size);	}
};

//instructions

typedef void instruction_func_t(Emulator*);	//各命令に対応した関数の型

void InitInstructions16(void);			//16bit命令の初期化
void InitInstructions32(void);			//32bit

extern instruction_func_t* instructions16[256];	//16bit命令の関数の配列
extern instruction_func_t* instructions32[256];	//32bit

#endif //EMULATOR_H_

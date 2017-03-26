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

// EFLAGS
#define CARRY_FLAG	(1)
#define ZERO_FLAG	(1 << 6)
#define SIGN_FLAG	(1 << 7)
#define OVERFLOW_FLAG	(1 << 11)

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

#define REGISTERS_COUNT32 8

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

//GDT,IDT関連
//GDTR,IDTR用のレジスタ型(48bit)
struct DTRegister {
	uint16_t table_limit;
	uint32_t base_addr;
};

//GDT
struct SEGMENT_DESCRIPTOR {
	uint16_t limit_low, base_low;
	uint8_t base_mid, access_right;
	uint8_t limit_high, base_high;
};

//IDT
struct GATE_DESCRIPTOR {
	uint16_t offset_low, selector;
	uint8_t dw_count, access_right;
	uint16_t offset_high;
};

//エミュレータクラス
class Emulator{
private:
	int BitMode;
	int memory_size;
public:
	Register CR[5];		// CR0 ~ CR4 制御レジスタ
	Register eflags;
	
	Register eip;
	DTRegister GDTR, IDTR;
	
	Register reg[REGISTERS_COUNT];
	
	uint8_t *memory;
public:				// member funcs
	Emulator();
	~Emulator();

	void InitRegisters();

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

	void Push32(uint32_t val);
	uint32_t Pop32();

	// EFLAGSの各フラグ取得
	int IsCarry()	{ return (EFLAGS & CARRY_FLAG)	 != 0; }
	int IsZero()	{ return (EFLAGS & ZERO_FLAG)	 != 0; }
	int IsSign()	{ return (EFLAGS & SIGN_FLAG)	 != 0; }
	int IsOverflow(){ return (EFLAGS & OVERFLOW_FLAG)!= 0; }

	// EFLAGSの各フラグ設定
	void SetCarry(int is_carry);
	void SetZero(int is_zero);
	void SetSign(int is_sign);
	void SetOverflow(int is_overflow);

	//関数名がキモいけどとりあえず放置
	void UpdateEflagsSub(uint32_t v1, uint32_t v2, uint64_t result);

	void DumpRegisters(int bit);		//各レジスタの値を標準入出力に書き込む。引数はビットモード。
	void DumpRegisters();
	void DumpMemory(const char *fname, uint32_t addr, uint32_t size);
	void DumpMemory(const char *fname, uint32_t size){	DumpMemory(fname, 0x00, size);	}
	void DumpMemory(const char *fname){	DumpMemory(fname, memory_size);	}
};

//instructions

typedef void instruction_func_t(Emulator*);	//各命令に対応した関数の型

void InitInstructions16(void);			//16bit命令の初期化
void InitInstructions32(void);			//32bit

extern instruction_func_t* instructions16[256];	//16bit命令の関数の配列
extern instruction_func_t* instructions32[256];	//32bit

//eflgas

#endif //EMULATOR_H_

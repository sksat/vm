#ifndef MEMORY_H_
#define MEMORY_H_

#include <stdio.h>
#include <stdint.h>

class Memory {
public:
	Memory(size_t size);
	~Memory();
	void Init(size_t size);

	uint8_t operator [] (int addr);

	void LoadBinary(const char *fname, uint32_t addr, int size);
	void Dump(const char *fname, uint32_t addr, size_t size);
private:
	size_t size;
	uint8_t *mem;
};

#endif // MEMORY_H_

#include "Memory.h"

Memory::Memory(size_t size){
	Init(size);
}

Memory::~Memory(){
	if(mem == NULL) return;
	delete[] mem;
}

void Memory::Init(size_t size){
	mem = new uint8_t[size];
	this->size = size;
}

void Memory::LoadBinary(const char *fname, uint32_t addr, int size){
	FILE *fp;
	fp = fopen(fname, "rb");
	if(fp == NULL)	throw "Memory: caan't load binary";
	fread(mem + addr, 1, size, fp);
	fclose(fp);
}

void Memory::Dump(const char *fname, uint32_t addr, size_t size){
	if(this->size < addr) throw "Memory: can't dump";
	if(this->size < (addr+size)){
		size = this->size - addr;
	}
	FILE *fp;
	fp = fopen(fname, "wb");
	if(fp == NULL) throw "Memory: can't open file";
	fwrite(mem+addr, sizeof(uint8_t), size, fp);
	fclose(fp);
}

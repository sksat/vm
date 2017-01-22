
void boxfill8(unsigned char *vram, int xsize, unsigned char c,  int x0, int y0, int x1, int y1);
int add(int a, int b);

int start(){
	char *vram;
	int i, xsize, ysize;
	vram = (char*)0xa0000;
	xsize = 320;
	ysize = 200;
	
	for(i=(int)vram; i<=0xaffff; i++){
		char *p;
		p = (char*)i;
		*p = i & 0x0f;
	}
	
//	boxfill8(vram, xsize, 1, 20, 20, 120, 120);
loop:
//	return add(2, 5);
	goto loop;
}

int add(int a, int b){
        return a + b;
}

void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1){
        int x,y;
        for(y=y0; y<=y1; y++){
                for(x=x0; x<=x1; x++){
                        vram[y*xsize + x] = c;
                }
        }
        return;
}



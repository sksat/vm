#include <stdio.h>

#include "PPM.h"

using namespace sksat;

PPM::PPM(){
	
}

PPM::~PPM(){
	
}

void PPM::Write(const char *fname){
	FILE *fp;
	
	type = 3;
	
	fp = fopen(fname, "wb");
	
	fprintf(fp, "P%d\n", type);
	fprintf(fp, "%u %u\n", this->xsize, this->ysize);
	if(type != 1 && type != 4){
		fprintf(fp, "255\n");
	}
	
	for(int y=0;y<this->ysize;y++){
	for(int x=0;x<this->xsize;x++){
		for(int i=0;i<3;i++){
			fprintf(fp, "%u", data[(y*this->xsize + x)*4 + i]);
			if(i!=2){
				fprintf(fp, " ");
			}else{
				fprintf(fp, "\n");
			}
		}
	}
	}
	
	fclose(fp);
	return;
}



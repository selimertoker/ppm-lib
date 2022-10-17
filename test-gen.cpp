
#include<iostream>
#include<fstream>
#include<math.h>
#include "ppm-lib.h"

int main(int argc,char** argv){
	image img(512,512,255);
	for(int y=0;y<img.height;y++)
	{
		for(int x=0;x<img.width;x++)
		{
			int color[3]={x/2,128,y/2};
			img.setpxl(x,y,color);
		}
	}
	img.savefile(argv[1]);
	return 0;
}


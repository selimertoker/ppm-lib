// image sequence adder, adds by arithmetic mean
#include <iostream>
#include<fstream>
#include "ppm-lib.h"

int main(int argc,char** argv){
	if(argc==1){
		std::cout<<"radon image merge program, merges by aarithmetic mean\nUsage: merge out_file in(min) in(max)\n";
		return 0;
	}
	image buf(512,512,255);
//	buf.reset();
	int min=0;
	for(int i=0;i<4;i++){
		if ((int)argv[2][i]==0){break;}
		min=(min*10)+((int)argv[2][i]-48);
	}
	int max=0;
	for(int i=0;i<4;i++){
		if ((int)argv[3][i]==0){break;}
		max=(max*10)+((int)argv[3][i]-48);
	}
	for(int i=min;i<=max;i++){
		std::cout<<i<<'\n';
		image img(512,512,255);
		char fname[7]={0,0,0,0,0,0,0};
		int j;
		for(j=0;j<sizeint(i);j++){
			int theint=i;
			while(sizeint(theint)>(j+1)){theint/=10;}
			fname[j]=theint%10+48;
		}
		fname[j++]='.';fname[j++]='p';fname[j++]='p';fname[j++]='m';
		img.readfile(fname);
		int color[3];
		for(int y=0;y<buf.height;y++){
			for(int x=0;x<buf.width;x++){
				color[0]=buf.getpxl(x,y,0)+img.getpxl(x,y,0);
				color[1]=buf.getpxl(x,y,1)+img.getpxl(x,y,1);
				color[2]=buf.getpxl(x,y,2)+img.getpxl(x,y,2);
				buf.setpxl(x,y,color);
			}
		}
		free(img.buf);
		std::cout<<i<<"\r";
	}
	int color[3];
	for(int y=0;y<buf.height;y++){
		for(int x=0;x<buf.width;x++){
			color[0]=buf.getpxl(x,y,0)/(max-min);
			color[1]=buf.getpxl(x,y,1)/(max-min);
			color[2]=buf.getpxl(x,y,2)/(max-min);
			buf.setpxl(x,y,color);
		}
		std::cout<<y<<"\r";
	}
	buf.savefile(argv[1]);
	return 0;
}

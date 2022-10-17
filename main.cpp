
#include<iostream>
#include<fstream>
#include"ppm-lib.h"

int main(int argc,char** argv){
if(argc==1){std::cout<<"no input?\n"; return 0;}
image img(1,256,255);
std::cout<<"reading "<<argv[1]<<"\n";
std::cout<<img.height<<'x'<<img.width<<'\n';
img.readfile(argv[1]);
int color[3];
for(int i=0;i<img.height*img.width;i++){
	color[0]=img.getpxl(i,0,0);
	color[1]=img.getpxl(i,0,1);
	color[2]=img.getpxl(i,0,2);
	std::cout<<i<<' '<<color[0]<<'x'<<color[1]<<'x'<<color[2]<<'\n';
	img.setpxl(i,0,color);
	}
img.savefile(argv[1]);
}

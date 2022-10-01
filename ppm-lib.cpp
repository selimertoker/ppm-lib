
#include<iostream>
#include<fstream>

#include "ppm-lib.h"

bool help(int argc,char** argv){
	if(
			(argc==2)
			||
			(
			 ((argv[1][0]=='-')&&(argv[1][1]=='h'))
			 ||
			 ((argv[1][1]=='-')&&(argv[1][2]=='h')&&(argv[1][3]=='e')&&(argv[1][4]=='l')&&(argv[1][5]=='p'))
			)
	  )
	{return true;}
	return false;
}

int sizeint(int a){
	int i=1;
	while(a >=10){a /=10;i++;}
	return i;
}
int* sizeimg(char* filen)
{
	std::ifstream fileh;
	fileh.open(filen,std::ios::binary|std::ios::in);
	char x;
	int i=0;
	char magic[2];

	fileh.read(&x,1);
	magic[0]=(char)x;

	fileh.read(&x,1);
	magic[1]=(char)x;

	fileh.read(&x,1);

	int* size=(int*)malloc(3*sizeof(int));
	int theint;

	theint=0;
	while(1){
		fileh.read(&x,1);
		if((char)x==' '){size[0]=theint;break;}
		theint=theint*10+(int)x-48;}

	theint=0;
	while(1){
		fileh.read(&x,1);
		if((char)x=='\n'){size[1]=theint;break;}
		theint=theint*10+(int)x-48;}
	theint=0;
	while(1){
		fileh.read(&x,1);
		if((char)x=='\n'){size[2]=theint;break;}
		theint=theint*10+(int)x-48;}
	fileh.close();
	return size;
}
int* readimg(char* filen)
{
	std::ifstream fileh;
	fileh.open(filen,std::ios::binary|std::ios::in);
	char x;
	int i=0;
	char magic[2];

	fileh.read(&x,1);
	magic[0]=(char)x;

	fileh.read(&x,1);
	magic[1]=(char)x;

	if((magic[0]!='P')||(magic[1]!='6')){std::cout<<"not a P6 file!\n";}

	fileh.read(&x,1);

	int size[3];
	int theint;

	theint=0;
	while(1){
		fileh.read(&x,1);
		if((char)x==' '){size[0]=theint;break;}
		theint=theint*10+(int)x-48;}

	theint=0;
	while(1){
		fileh.read(&x,1);
		if((char)x=='\n'){size[1]=theint;break;}
		theint=theint*10+(int)x-48;}
	theint=0;
	while(1){
		fileh.read(&x,1);
		if((char)x=='\n'){size[2]=theint;break;}
		theint=theint*10+(int)x-48;}

	int* buf=(int*)malloc(size[0]*size[1]*3*sizeof(int));

	for(i=0;i<size[0]*size[1]*3;i++)
	{
		fileh.read(&x, 1);
		if(x<0){buf[i]=(int)x+256;}
		else{buf[i]=(int)x;}
		if(x==EOF){break;}
	}
	fileh.close();
	return buf;
}

int writeimg(int* buf,int* size,char* filen)
{
	std::ofstream fileh;
	fileh.open(filen,std::ios::binary|std::ios::out);
	fileh.write("P6",2);
	fileh.write("\n",1);


	for(int i=0;i<sizeint(size[0]);i++){
		int theint=size[0];
		while(sizeint(theint)>(i+1)){theint/=10;}
		theint%=10;
		char ch=theint+48;
		fileh.write(&ch,1);}

	fileh.write(" ",1);

	for(int i=0;i<sizeint(size[1]);i++){
		int theint=size[1];
		while(sizeint(theint)>(i+1)){theint/=10;}
		theint%=10;
		char ch=theint+48;
		fileh.write(&ch,1);}

	fileh.write("\n",1);

	for(int i=0;i<sizeint(size[2]);i++){
		int theint=size[2];
		while(sizeint(theint)>(i+1)){theint/=10;}
		theint%=10;
		char ch=theint+48;
		fileh.write(&ch,1);}

	fileh.write("\n",1);

	for(int i=0;i<size[0]*size[1]*3;i++)
	{
		if(buf[i]>128){char ch=buf[i]-256;}
		else{char ch=buf[i];}
		char ch=buf[i];
		fileh.write(&ch, 1);
	}
	fileh.write("\n",1);
	fileh.close();
	return 0;
}

int* newimg(int* size)
{
	int* buf=(int*)malloc(size[0]*size[1]*3*sizeof(int));
	return buf;
}
int setpxl(int* buf,int* size,int x,int y,int* color)
{
	int pxlindex=3*(size[0]*y+x);
	buf[pxlindex+0]=color[0];
	buf[pxlindex+1]=color[1];
	buf[pxlindex+2]=color[2];
	return 0;
}
int* getpxl(int* buf,int* size,int x,int y){
	int pxlindex=3*(size[0]*y+x);
//	if(buf[pxlindex]<0){std::cout<<buf[pxlindex]<<' '<<x<<' '<<y<<std::endl;}
	static int color[3]={buf[pxlindex+0],buf[pxlindex+1],buf[pxlindex+2]};
	return color;
}

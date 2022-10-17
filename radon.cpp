
#include<iostream>
#include<fstream>
#include<math.h>
#include "ppm-lib.h"
int ray(image refimg,image radimg,char* fname,int degree,int R){
	image img((R+1)*2,(R+1)*2,255);
	float sin=std::sin(degree*M_PI/180);
	float cos=std::cos(degree*M_PI/180);
	int cord[2];
	int index;
	int line[3]={0,0,0};
	for(int rof=-R;rof<R;rof++){
		for(int r=-R;r<R;r++){
			cord[0]=(int)(R+(r*cos-rof*sin)/(std::sqrt(2)));
			cord[1]=(int)(R+(r*sin+rof*cos)/(std::sqrt(2)));
			index=3*(cord[0]+cord[1]*refimg.width);
			line[0]+=refimg.buf[index+0];
			line[1]+=refimg.buf[index+1];
			line[2]+=refimg.buf[index+2];
		}
		line[0]/=(R*2);
		line[1]/=(R*2);
		line[2]/=(R*2);
		radimg.setpxl(degree,rof+R,line); //radon image
		for(int r=-R;r<R;r++){
			cord[0]=(int)(R+(r*cos-rof*sin)/(std::sqrt(2)));
			cord[1]=(int)(R+(r*sin+rof*cos)/(std::sqrt(2)));
			img.setpxl(cord[0],cord[1],line);
		}
	}
	img.savefile(fname);
	return 0;
}
/*
int ray(image refimg,image radimg,char* fname,int degree,int R){
	image img((R+1)*2,(R+1)*2,255);
	float sin=std::sin(degree*M_PI/180);
	float cos=std::cos(degree*M_PI/180);
	int cord[2];
	int line[3];
	for(int rof=-R;rof<R;rof++){
		for(int r=-R;r<R;r++){
			cord[0]=(int)(R+(r*cos-rof*sin)/(std::sqrt(2)));
			cord[1]=(int)(R+(r*sin+rof*cos)/(std::sqrt(2)));
			line[0]+=refimg.getpxl(cord[0],cord[1],0);
			line[1]+=refimg.getpxl(cord[0],cord[1],1);
			line[2]+=refimg.getpxl(cord[0],cord[1],2);
		}
		line[0]/=R;
		line[1]/=R;
		line[2]/=R;
		radimg.setpxl(degree,rof+R,line); //radon image
		for(int r=-R;r<R;r++){
			cord[0]=(int)(R+(r*cos-rof*sin)/(std::sqrt(2)));
			cord[1]=(int)(R+(r*sin+rof*cos)/(std::sqrt(2)));
			img.setpxl(cord[0],cord[1],line);
		}
	}
	img.savefile(fname);
	return 0;
}
*/
int main(int argc,char** argv){
	if(argc==1){std::cout<<"radon transform program\nUsage: radon in_file out_dir radon_file <degree_min> <degree_max>\n";return 0;}

	int min=0;
	int max=0;
	int j;

	image radimg(180,512,255); //radon transform image
	image refimg(512,512,255); //referance image
	radimg.readfile(argv[3]);
	refimg.readfile(argv[1]);

	for(int i=0;i<4;i++){
		if((int)argv[4][i]==0){break;}
		min=(min*10)+((int)argv[4][i]-48);} //gets degree (char* to int)
	for(int i=0;i<4;i++){
		if((int)argv[5][i]==0){break;}
		max=(max*10)+((int)argv[5][i]-48);} //gets degree (char* to int)
	if((max<min)||(max<0)||(max>360)||(min<0)||(min>360)){std::cout<<"WRONG ANGLE"; return 1;}
	for(int i=min;i<=max;i++){
		char fname[7]={0,0,0,0,0,0,0};
		for(j=0;j<sizeint(i);j++){
			int theint=i;
			while(sizeint(theint)>(j+1)){theint/=10;}
			fname[j]=theint%10+48;
		}
		fname[j++]='.';fname[j++]='p';fname[j++]='p';fname[j++]='m';
		ray(refimg,radimg,fname,i,255);
	}

	radimg.savefile(argv[3]);
	return 0;
}


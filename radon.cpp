
#include<iostream>
#include<fstream>
#include<math.h>
#include "ppm-lib.h"
int ray(image refimg,image radimg,char* fname,int degree,int R){
	image img((R+1)*2,(R+1)*2,255);
	img.reset();
	float sin=std::sin(degree*M_PI/180);
	float cos=std::cos(degree*M_PI/180);
	int cord[2];
	int index;
	int line[3]={0,0,0};
	for(int rof=-R;rof<R;rof++){
		int pxlcnt=0;
		for(int r=-R;r<R;r++){
			pxlcnt++;
			cord[0]=(int)(R+(r*cos-rof*sin));
			cord[1]=(int)(R+(r*sin+rof*cos));
			if ((cord[0]<0) || (cord[0]>2*R)) {continue;}
			if ((cord[1]<0) || (cord[1]>2*R)) {continue;}
			//cord[0]=(int)(R+(r*cos-rof*sin)/(std::sqrt(2)));
			//cord[1]=(int)(R+(r*sin+rof*cos)/(std::sqrt(2)));
			index=3*(cord[0]+cord[1]*refimg.width);
			line[0]+=refimg.buf[index+0];
			line[1]+=refimg.buf[index+1];
			line[2]+=refimg.buf[index+2];
		}
		line[0]/=pxlcnt;
		line[1]/=pxlcnt;
		line[2]/=pxlcnt;
		radimg.setpxl(degree,rof+R,line); //radon image
		for(int r=-R;r<R;r++){
			cord[0]=(int)(R+(r*cos-rof*sin));
			cord[1]=(int)(R+(r*sin+rof*cos));
			//cord[0]=(int)(R+(r*cos-rof*sin)/(std::sqrt(2)));
			//cord[1]=(int)(R+(r*sin+rof*cos)/(std::sqrt(2)));
			img.setpxl(cord[0],cord[1],line);
		}
	}
	img.savefile(fname);
	free(img.buf);
	return 0;
}

int main(int argc,char** argv){

	if(argc==1){std::cout<<"radon transform program\nUsage: radon in_file radon_file <degree_min> <degree_max>\n";return 0;}

	int min=0;
	int max=0;
	int j;

	image radimg(180,512,255); //radon transform image
	image refimg(512,512,255); //referance image
	radimg.readfile(argv[2]);
	refimg.readfile(argv[1]);

	for(int i=0;i<4;i++){
		if((int)argv[3][i]==0){break;}
		min=(min*10)+((int)argv[3][i]-48);} //gets degree (char* to int)

	for(int i=0;i<4;i++){
		if((int)argv[4][i]==0){break;}
		max=(max*10)+((int)argv[4][i]-48);} //gets degree (char* to int)

	if((max<min)||(max<0)||(max>360)||(min<0)||(min>360)){std::cout<<"WRONG ANGLE"; return 1;}
	for(int i=min;i<=max;i++){
		std::cout<<i<<"\n";
		char fname[7]={0,0,0,0,0,0,0};
		for(j=0;j<sizeint(i);j++){
			int theint=i;
			while(sizeint(theint)>(j+1)){theint/=10;}
			fname[j]=theint%10+48;
		} // generate filename
		fname[j++]='.';fname[j++]='p';fname[j++]='p';fname[j++]='m';

		ray(refimg,radimg,fname,i,255);
	}

	radimg.savefile(argv[2]);
	return 0;
}


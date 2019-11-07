#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define XOR0111 21                           //0b01010100
#define XOR0222 42                          //0b10101000
#define XOR0333 63                          //0b11111100

#define XOR1111 85                           //0b01010100
#define XOR2222 170                          //0b10101010

#define N_CHARS(l) ((1<<((l-1)<<1))>>1)
#define CONCAT_STP(A,s,k) (A[k] |= s)
/*
char m[4] = {76,        //1 0 3 0
             24,        //0 1 2 0
             228,		//3 2 1 0
             176};		//2 3 0 0
*/
unsigned char m[4] = {36,
		      49,
		      14,
		      27};


int i = 0;
int j = 0;

int x,y,z;
clock_t start, end;
double cpu_time_used;

void xor(unsigned char *curve,
		 unsigned char *s1,
		 unsigned char *s2,
		 unsigned char *s3,
		 int chars){

	int ceil = chars - 1;
	int offset_q2 = chars;
	int offset_q3 = chars * 2;
	int offset_q4 = chars * 3;

	for(int c=0; c < ceil; c++){
		curve[c + offset_q2] = curve[c] ^ XOR1111;
		curve[c + offset_q3] = curve[c] ^ XOR1111;
		curve[c + offset_q4] = curve[c] ^ XOR2222;
	}
  
	curve[ceil + offset_q2] = curve[ceil] ^ XOR0111;
	curve[ceil + offset_q3] = curve[ceil] ^ XOR0111;
	curve[ceil + offset_q4] = curve[ceil] ^ XOR0222;
    
	CONCAT_STP(curve, (*s1)^=64, offset_q2-1);
	CONCAT_STP(curve, (*s2)^=64, offset_q3-1);
	CONCAT_STP(curve, (*s3)^=64, offset_q4-1);
}


unsigned char* hilbert_curve(unsigned int level, int d){

	//Init Aux Vars
	unsigned char s1 = (d==3)?192:128;
	unsigned char s2 = (d==3)?128:192;
	unsigned char s3 = (d==3)?64:0;

	//Alloc Curve 
	unsigned char* path = (char*)malloc(sizeof(char) * N_CHARS(level));

	switch(level){
	case 0:
		exit(-1);

	case 1:                                 //level 1
		path = (char*)malloc(sizeof(char));
		path[0] = (d == 3)? 2: 3;
		return path;

	default:                                //level >= 2
		path = (char*)malloc(sizeof(char) * N_CHARS(level));
		path[0] = (d == 3)?235:190;
		path[1] = (d == 3)?18:7;
	}

	//Main Loop
	for(int l = 1; l < level; l++){ 
		xor(path, &s1, &s2, &s3, N_CHARS(l)); 
	}
	return path;
}


void process_d(int d){
	int val,dir;	    

	val = m[d];
    
	dir = val % 4;
    	val = val / 4;
	j += (dir-1) % 2;
	i += (dir-2) % 2;

	dir = val % 4;
    	val = val / 4;
	j += (dir-1) % 2;
	i += (dir-2) % 2;

	dir = val % 4;
	j += (dir-1) % 2;
	i += (dir-2) % 2;
}

void process_path(unsigned char *a, int size){
	int d;
	unsigned char p;

	if(size == 1){
		process_d(a[0]);
		return;
	}

	for(int c = 0; c < size - 1; c++){
		p = a[c];
	    
		d = p % 4;
		p = p / 4;
		process_d(d);

		d = p % 4;
		p = p / 4;
		j += (d-1) % 2;
		i += (d-2) % 2;

		d = p % 4;
		p = p / 4;
		process_d(d);

		d = p % 4;
		j += (d-1) % 2;
		i += (d-2) % 2;
	}

	p = a[size-1];
	d = p % 4;
	p = p / 4;
	process_d(d);

	d = p % 4;
	p = p / 4;
	j += (d-1) % 2;
	i += (d-2) % 2;

	d = p % 4;
	process_d(d);

	x = i;
	y = j;
	z = d;
}



int main(int argc, char** argv){
    
	unsigned int n = atoi(argv[1]);
	int d = atoi(argv[2]);
	unsigned int L = 0;

	unsigned int tmp = n;
	while(tmp>>=1){ ++L; }


	start = clock();

	unsigned char *p;
	p = hilbert_curve(L,d);
	process_path(p,N_CHARS(L));

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("%f\n", cpu_time_used);
	return 0;
}


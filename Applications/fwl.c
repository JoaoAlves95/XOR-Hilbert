#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<time.h>
#include"matrix_gen.h"

int l = 0;
int a = 0;
int d = 3;
unsigned long long h = 0;
unsigned long long i = 0;
unsigned long long j = 0;

clock_t start, end;
double cpu_time_used;

int odd = 0;

int main(int argc, char** argv){

	unsigned long long n = atoi(argv[1]);
	unsigned long long N = n * n;
	unsigned long long tmp = n;

	int **W = matrix_gen_int(n,n,4);

	//log2(n)
  	unsigned int r = 0;
	while (tmp >>= 1){ ++r; }

	int d = atoi(argv[2]);
  
  	start = clock();      
	while(h < N){

		// assume W was trasnposed beforehand
		for(int k=0; k < n; k++)
			if (W[j][i] + W[i][k] < W[j][k])  
				W[j][k] = W[j][i] + W[i][k];
		h++;
		l = h & -h;
		l = (l + l/2) & 0x5555555555555555ull;
		a = (h/ l) & 3 ;
		odd = (l & 0xCCCCCCCCCCCCCCCCull) != 0;
		d ^= 3 * ((a==3) != odd);
		i += (d - 2) % 2;
		j += (d - 1) % 2;
		d ^= ((a==1) != odd);
	}
  	end = clock();
  	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  	printf("%d, %f\n", r, cpu_time_used);
  	return 0;
}

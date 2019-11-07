#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "matrix_gen.h"

clock_t start, end;
double cpu_time_used;
unsigned int x,y,z;     

int main(int argc, char** argv){
	//#elements in row/col
	unsigned int n = atoi(argv[1]);
	unsigned int r = 0;
	unsigned int tmp = n;

	//curve resolution
	while (tmp >>= 1){ ++r; }
	
	int **A = matrix_gen_int(n,n,7);
	int **B = matrix_gen_int(n,n,7);
	int **S = matrix_gen_int(n,n,0);
  	start = clock();
	
	mat_mult_naive(A,B,S,n,n);
	
	end = clock();
  	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
 
  	printf("%d, %f\n", r, cpu_time_used);
 	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix_gen.h"

clock_t start, end;
double cpu_time_used;

int main(int argc, char* argv[]){

	unsigned int v = atoi(argv[1]);

	unsigned int r = 0;
	unsigned int tmp = v;
	while (tmp >>= 1) { ++r; }

	int **W = matrix_gen_int(v,v,4);
	
	start = clock();

	fw_int(W,v);
	
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("%d, %f\n", r, cpu_time_used);
	return 0;
}

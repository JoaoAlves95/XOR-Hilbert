#include "furhilbert.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "matrix_gen.h"

int main(int argc, char** argv){
	unsigned long long i_max = atoi(argv[1]);
	unsigned long long j_max = atoi(argv[2]);
	unsigned long long n = i_max;

	clock_t start, end;
	double cpu_time_used;

	//log2(n)
	unsigned int r = 0;
	unsigned int tmp = i_max;
	while (tmp >>= 1) { ++r; }

	int **A = matrix_gen_int(i_max,j_max,7);
	int **B = matrix_gen_int(i_max,j_max,7);
	int **T = matrix_gen_int(i_max,j_max,0);
	int **S = matrix_gen_int(i_max,j_max,0);
	start = clock();

	//transpose
	int i, j, h = 0;
	FUR_HILBERT_FOR(i, j, 0, i_max, 0, j_max) {
	
		T[j][i] += B[i][j];
	
	} FUR_HILBERT_END(i, j); end = clock();

	//multiply
	i, j, h = 0;
	FUR_HILBERT_FOR(i, j, 0, i_max, 0, j_max) {
	
		for(int k = 0; k < j_max; k++)
			S[i][j] += A[i][k] * T[j][k];
	
	} FUR_HILBERT_END(i, j);

	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

	printf("%d, %f\n", r, cpu_time_used);
}

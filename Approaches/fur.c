#include "furhilbert.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char** argv){
	int i_max = atoi(argv[1]);
	int j_max = atoi(argv[2]);

	clock_t start, end;
	double cpu_time_used;

	//log2(n)
	unsigned int r = 0;
	unsigned int tmp = i_max;
	while (tmp >>= 1) { ++r; }

	start = clock();

	int i, j, h = 0;
	FUR_HILBERT_FOR(i, j, 0, i_max, 0, j_max) {
	} FUR_HILBERT_END(i, j); end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("%f\n",cpu_time_used);
}

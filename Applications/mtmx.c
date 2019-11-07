#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#include "matrix_gen.h"

#define XOR0111 21                           //0b01010100
#define XOR0222 42                          //0b10101000
#define XOR0333 63                          //0b11111100

#define XOR1111 85                           //0b01010100
#define XOR2222 170                          //0b10101010
#define XOR3333 255                          //0b11111111

#define N_CHARS(l)(1<<((l-1)<<1))			 //(4**(l-1))
#define CONCAT_STP(A,s,k) (A[k] |= s)

     
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

	//Init Curve 

	path[0] = (d == 3)? 27: 14;

	//Main Loop
	for(int l = 1; l < level; l++) { 
		xor(path, &s1, &s2, &s3, N_CHARS(l)); 
	}

	return path;
}


void process_path_transposition(unsigned char *a,
                                int** A,
                                int** T,
                                unsigned int n,
                                int size){

  int i, j, d;
  unsigned long long sum;
  register unsigned char p;
  i = 0;
  j = 0;

  T[j][i] = A[i][j];

  for(int c = 0; c < size - 1; c++){
    p = a[c];
      
    d = p % 4;
    p = p / 4;
    j += (d-1) % 2;
    i += (d-2) % 2;

    T[j][i] = A[i][j];

    d = p % 4;
    p = p / 4;
    j += (d-1) % 2;
    i += (d-2) % 2;
    
    T[j][i] = A[i][j];

    d = p % 4;
    p = p / 4;
    j += (d-1) % 2;
    i += (d-2) % 2;

    T[j][i] = A[i][j];

    d = p % 4;
    j += (d-1) % 2;
    i += (d-2) % 2;
    
    T[j][i] = A[i][j];
  }

  p = a[size-1];
  d = p % 4;
  p = p / 4;
  j += (d-1) % 2;
  i += (d-2) % 2;

  T[j][i] = A[i][j];

  d = p % 4;
  p = p / 4;
  j += (d-1) % 2;
  i += (d-2) % 2;
  
  T[j][i] = A[i][j];

  d = p % 4;
  j += (d-1) % 2;
  i += (d-2) % 2;

  T[j][i] = A[i][j];
}

void process_path_multiplication(unsigned char *a, int **A,
                                 int** B,
                                 int** S,
                                 unsigned int n,
                                 int size){

  int i, j, d;
  unsigned long long sum;
  register unsigned char p;
  i = 0;
  j = 0;

  for (int k = 0; k < n; k++) {
    S[i][j] += A[i][k]*B[j][k];
  }

  for(int c = 0; c < size - 1; c++){
    p = a[c];
      
    d = p % 4;
    p = p / 4;
    j += (d-1) % 2;
	  i += (d-2) % 2;

    for (int k = 0; k < n; k++) {
      S[i][j] += A[i][k]*B[j][k];
    }
    
    d = p % 4;
    p = p / 4;
    j += (d-1) % 2;
  	i += (d-2) % 2;
    
    for (int k = 0; k < n; k++) {
      S[i][j] += A[i][k]*B[j][k];
    }

    d = p % 4;
    p = p / 4;
    j += (d-1) % 2;
  	i += (d-2) % 2;

    for (int k = 0; k < n; k++) {
      S[i][j] += A[i][k]*B[j][k];
    }

    d = p % 4;
    j += (d-1) % 2;
  	i += (d-2) % 2;
    
    for (int k = 0; k < n; k++) {
      S[i][j] += A[i][k]*B[j][k];
    }
  }

  p = a[size-1];
  d = p % 4;
  p = p / 4;
  j += (d-1) % 2;
	i += (d-2) % 2;

  for (int k = 0; k < n; k++) {
    S[i][j] += A[i][k]*B[j][k];
  }

  d = p % 4;
  p = p / 4;
  j += (d-1) % 2;
	i += (d-2) % 2;
  
  for (int k = 0; k < n; k++) {
    S[i][j] += A[i][k]*B[j][k];
  }

  d = p % 4;
  j += (d-1) % 2;
  i += (d-2) % 2;

  for (int k = 0; k < n; k++) {
    S[i][j] += A[i][k]*B[j][k];
  }
}

int main(int argc, char** argv){
  //#elements in row/col
  unsigned int n = atoi(argv[1]);
  unsigned int d = atoi(argv[2]);
  unsigned int r = 0;
  unsigned int tmp = n;

  //curve resolution
  while (tmp >>= 1){ ++r; }

  int **A = matrix_gen_int(n,n,7);
  int **B = matrix_gen_int(n,n,7);
  int **T = matrix_gen_int(n,n,0);
  int **S = matrix_gen_int(n,n,0);
  start = clock();

  unsigned char* p = hilbert_curve(r,d);

  process_path_transposition(p, B, T, n, N_CHARS(r));
  process_path_multiplication(p, A, T, S, n, N_CHARS(r));

  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("%d, %f\n", r, cpu_time_used);
  return 0;
}

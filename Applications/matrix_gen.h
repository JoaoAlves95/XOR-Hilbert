#include<limits.h>
#include<float.h>
#include <stdlib.h>

/*
* matrix generator
* i_max: array length
* j_max: array width
* flg==0: all zeros
* flg==1: all ones
* flg==2: crescent order
* returns pointer to generated matrix
* */

#define MAX 99

char* fill_cache(){
	const int size = 26*1024*1024; // Allocate 20M. Set much larger then L2
	char *c = (char *)malloc(size);
	for (int i = 0; i < 0xffff; i++)
	       for (int j = 0; j < size; j++)
		       c[j] = i*j;
	return c;
}


unsigned long long** matrix_gen(unsigned int i_max, unsigned int j_max, int flg){

	unsigned long long** M = (unsigned long long**) malloc(sizeof(unsigned long long*) * (unsigned long long)j_max);

	for(int j=0; j < j_max; j++){
		M[j] = malloc(sizeof(unsigned long long) * (unsigned long long)i_max);
	}

	if(M == NULL){
		perror("unsucessful malloc\n");
		exit(-1);
	}

	unsigned long long n = 0;
	
	switch(flg){
		case 0:
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){	
					M[i][j] = (unsigned long long)0;
				}
			}
			break;

		case 1:
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){	
					M[i][j] = (unsigned long long)1;
				}
			}
			break;

		case 2:
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){
					M[i][j] = (unsigned long long)n;
					n++;
				}
			}
			break;

		case 3:
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){
					if(i!=j)
						M[i][j] = (unsigned long long)0;
					else
						M[i][j] = (unsigned long long)1;
				}
			}
			break;
	   //weight matrix for floyd-warshall
	   case 4:
	    	for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){
					if(i==0)
						M[i][j] = ULLONG_MAX;
					else
						M[i][j] = i;
				}
			}
			break; 

		//initial matrix for floyd-warshall
		case 5:
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){
					M[i][j] = (double)i;
				}
			}
			break;
		}


	return M;
}


double** matrix_gen_double(unsigned int i_max, unsigned int j_max, int flg){

	double** M = (double**) malloc(sizeof(double*) * i_max);

	for(int j=0; j < j_max; j++){
		M[j] = malloc(sizeof(double) * j_max);
	}

	if(M == NULL){
		perror("unsucessful malloc\n");
		exit(-1);
	}

	unsigned long long n = 0;
	
	switch(flg){
		case 0:
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){	
					M[i][j] = (double)0;
				}
			}
			break;

		case 1:
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){	
					M[i][j] = (double)1;
				}
			}
			break;

		case 2:
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){
					M[i][j] = (double)n;
					n++;
				}
			}
			break;

		case 3:
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){
					if(i!=j)
						M[i][j] = (double)0;
					else
						M[i][j] = (double)1;
				}
			}
			break;
   		//weight matrix for floyd-warshall
   		case 4:
		    for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){
					M[i][j] = DBL_MAX;
				}
			}
			break; 

		//initial matrix for floyd-warshall
		case 5:
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){
					M[i][j] = (double)i;
				}
			}
			break;
	}
	return M;

}

double* matrix_gen_dbl(unsigned int i_max, unsigned int j_max, int flg){
	
	double* M = (double*) malloc(sizeof(double) * j_max * i_max);

	if(M == NULL){
		perror("unsucessful malloc\n");
		exit(-1);
	}

	double n = 0;
	
	switch(flg){
		case 0:
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){	
					M[i * j_max + j] = 0.0;
				}
			}
			break;

		case 1:
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){	
					M[i * j_max + j] = 1.0;
				}
			}
			break;

		case 2:
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){
					M[i * j_max + j] = n;
					n++;
				}
			}
			break;

		case 3:
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){
					if(i!=j)
						M[i * j_max + j] = 0.0;
					else
						M[i * j_max + j] = 1.0;
				}
			}
			break;

   		//distance matrix for floyd-warshall
   		case 4:
      			for(unsigned int i=0; i < i_max; i++)
				for(unsigned int j=0; j < j_max; j++)
					M[i * j_max + j] = DBL_MAX;
			break; 
		
		//transposed adjacency matrix for floyd-warshall
    		case 5:
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){	
					M[i * j_max + j] = i + 1.0;
				}
			}
			break;

    		case 6:
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){	
					M[i * j_max + j] = i + 1.0;
				}
			}
			break;
	}		
	return M;
}

int** matrix_gen_int(unsigned int i_max, unsigned int j_max, int flg){
	
	int** M = (int**) malloc(sizeof(int*) * j_max);

	for(int j=0; j < j_max; j++){
		M[j] = malloc(sizeof(int) * i_max);
	}

	if(M == NULL){
		perror("unsucessful malloc\n");
		exit(-1);
	}

	unsigned long long n = 0;
	
	switch(flg){
		case 0:
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){	
					M[i][j] = 0;
				}
			}
			break;

		case 1:
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){	
					M[i][j] = 1;
				}
			}
			break;

		case 2:
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){
					M[i][j] = n;
					n++;
				}
			}
			break;

		case 3:
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){
					if(i!=j)
						M[i][j] = 0;
					else
						M[i][j] = 1;
				}
			}
			break;

   		//distance matrix for floyd-warshall
   		case 4:
      			for(unsigned int i=0; i < i_max; i++)
				for(unsigned int j=0; j < j_max; j++)
					M[i][j] = -1;
			break; 
		
		//transposed adjacency matrix for floyd-warshall
    		case 5:
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){	
					M[j][i] = i+1;
				}
			}
			break;

    		case 6:
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){	
					M[i][j] = i+1;
				}
			}
			break;

		case 7:
			srand(time(NULL));
			for(unsigned int i=0; i < i_max; i++){
				for(unsigned int j=0; j < j_max; j++){	
					M[i][j] = rand() % 100;
				}
			}
	}		
	return M;
}

void populate_fw(int **M){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(i==j){
				M[i][j] = 0;
			}
		}
	}
	M[0][1] = 4;
	M[0][2] = 1;
	M[2][3] = 1;
	M[3][1] = 1;
}


void print_matrix_dbl(double* M, unsigned int i_max, unsigned int j_max){

	printf("//////////////////////\n");

	for (int i = 0; i < i_max; i++)
    {
    	printf("i:%d\t",i);
        for (int j = 0; j < j_max; j++)
        {
            printf("%f\t", M[i * j_max + j]);
        }
        printf("\n");
    }

	printf("//////////////////////\n");
}


void print_matrix(int** M,
				  unsigned int i_max,
				  unsigned int j_max){

	printf("//////////////////////\n");

	for (int i = 0; i < i_max; i++)
    {
    	printf("i:%d\t",i);
        for (int j = 0; j < j_max; j++)
        {
            printf("%d\t", M[i][j]);
        }
        printf("\n");
    }

	printf("//////////////////////\n");
}

void mat_trans_naive(int **M,
		     int **T,
		     unsigned int i_max,
		     unsigned int j_max){

	for (unsigned int i = 0; i < i_max; i++)
		for (unsigned int j = 0; j < j_max; j++)
			T[j][i] = M[i][j];
}

//assume B is not transposed
void mat_mult_naive(int **A,
		    int **B,
		    int **S,
		    unsigned int i_max,
		    unsigned int j_max){

	for(int i = 0; i < i_max; i++){
		for(int j = 0; j < j_max; j++){
			for (int k = 0; k < j_max; k++) {
	    		S[i][j] += A[i][k]*B[k][j];
	  		}
	  	}
	}
}

//assume B is already transposed
void mat_mult_transp(int **A,
		     int **B,
		     int **S,
		     unsigned int i_max,
		     unsigned int j_max){

	for(int i = 0; i < i_max; i++){
		for(int j = 0; j < j_max; j++){
			for (int k = 0; k < j_max; k++) {
	    		S[i][j] += A[i][k]*B[j][k];
	  		}
	  	}
	}
}

char* mkrndstr(unsigned int n) {

	static char set[] = "ABC";
	char *rnd;

    rnd = (char*) malloc(sizeof(char) * n + 1);
    if (rnd) {
        int l = (int) (sizeof(set) - 1);
        int k;
        for (int i = 0; i < n; i++) {        
            k = rand() % l;
            rnd[i] = set[k];
	    }
	    rnd[n] = '\0';
	}
	return rnd;
}

char* string_gen(unsigned int n,int flg){

	char *s = (char*)malloc(sizeof(char) * n);
   
	switch(flg){
		// test string A -> 4
		case 0:
			s = "TES";
			break;
			 
		// test string B -> 4
		case 1:
			s = "TEX";
			break;
		
		// test string A -> 4
		case 2:
			s = "TESTTESTTESTTEX";
			break;
			 
		// test string B -> 4
		case 3:
			s = "TEXTTESTTESTTES";
			break;

		// random string
		case 4:
			s = mkrndstr(n);
			break;
	}
	return s;
}

//taken from: https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/
/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int lcs(int **M, char *X, char *Y, int m, int n ) 
{  
	/* Following steps build L[m+1][n+1] in bottom up fashion. Note  
	that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
	for (unsigned int i=0; i<=m; i++){ 
		for (unsigned int j=0; j<=n; j++) 
		{
			if (i == 0 || j == 0) 
				M[i][j] = 0; 

			else if (X[i-1] == Y[j-1]) 
				M[i][j] = M[i-1][j-1] + 1; 

			else
				M[i][j] = (M[i-1][j] > M[i][j-1])? M[i-1][j] : M[i][j-1];
		}
	} 
     
   /* L[m][n] contains length of LCS for X[0..n-1] and Y[0..m-1] */
	return M[m][n];
} 

void fw_dbl(double** W, int v){
	for(int k = 0; k < v; k++){
		for(int i=0; i < v; i++){
			for(int j=0; j< v; j++){
				if (W[i][k] + W[k][j] < W[i][j]){ 
						W[i][j] = W[i][k] + W[k][j];
				}
			}
		}
	}
}

void fw_int(int** W, int v){
	for(int i=0; i < v; i++)
		for(int j=0; j < v; j++)	
			for(int k = 0; k < v; k++)
				W[j][k] = W[j][k] ^ ((W[j][k] ^ (W[j][i]+W[i][k])) & -(W[j][k] <  (W[j][i]+W[i][k])));
}

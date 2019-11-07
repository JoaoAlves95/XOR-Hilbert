//FUR
#include <string.h>
#include <stdlib.h>

#define XOR0111 21                           //0b01010100
#define XOR0222 42                          //0b10101000
#define XOR0333 63                          //0b11111100

#define XOR1111 85                           //0b01010100
#define XOR2222 170                          //0b10101010
#define XOR3333 255                          //0b11111111

#define N_CHARS(l)(1<<((l-1)<<1))			 //(4**(l-1))
#define CONCAT_STP(A,s,k) (A[k] |= s) 

#ifndef FURHILBERT_H
#define	FURHILBERT_H


unsigned long long HILLOOP_nanoprog[9][9][4][2] = { {
    { {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull} }, // 0 x 0
    { {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull} }, // 0 x 1
    { {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull} }, // 0 x 2
    { {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull} }, // 0 x 3
    { {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull} }, // 0 x 4
    { {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull} }, // 0 x 5
    { {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull} }, // 0 x 6
    { {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull} }, // 0 x 7
    { {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull} } }, // 0 x 8
  { { {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull} }, // 1 x 0
    { {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull} }, // 1 x 1
    { {0x0ull, 0x2ull}, {0x0ull, 0x2ull}, {0x2ull, 0x2ull}, {0x2ull, 0x2ull} }, // 1 x 2
    { {0x0ull, 0x4ull}, {0x0ull, 0x4ull}, {0x6ull, 0x4ull}, {0x6ull, 0x4ull} }, // 1 x 3
    { {0x0ull, 0x8ull}, {0x0ull, 0x8ull}, {0xeull, 0x8ull}, {0xeull, 0x8ull} }, // 1 x 4
    { {0x0ull, 0x10ull}, {0x0ull, 0x10ull}, {0x1eull, 0x10ull}, {0x1eull, 0x10ull} }, // 1 x 5
    { {0x0ull, 0x20ull}, {0x0ull, 0x20ull}, {0x3eull, 0x20ull}, {0x3eull, 0x20ull} }, // 1 x 6
    { {0x0ull, 0x40ull}, {0x0ull, 0x40ull}, {0x7eull, 0x40ull}, {0x7eull, 0x40ull} }, // 1 x 7
    { {0x0ull, 0x80ull}, {0x0ull, 0x80ull}, {0xfeull, 0x80ull}, {0xfeull, 0x80ull} } }, // 1 x 8
  { { {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull} }, // 2 x 0
    { {0x0ull, 0x3ull}, {0x0ull, 0x3ull}, {0x2ull, 0x3ull}, {0x2ull, 0x3ull} }, // 2 x 1
    { {0x8ull, 0xdull}, {0x8ull, 0xaull}, {0x6ull, 0xdull}, {0x6ull, 0xaull} }, // 2 x 2
    { {0x0ull, 0x1ull}, {0x30ull, 0x24ull}, {0x0ull, 0x1ull}, {0xeull, 0x24ull} }, // 2 x 3
    { {0x88ull, 0xd5ull}, {0xe0ull, 0x88ull}, {0x76ull, 0xd5ull}, {0x1eull, 0x88ull} }, // 2 x 4
    { {0x0ull, 0x1ull}, {0x3c0ull, 0x210ull}, {0x0ull, 0x1ull}, {0x3eull, 0x210ull} }, // 2 x 5
    { {0x888ull, 0xd55ull}, {0xf80ull, 0x820ull}, {0x776ull, 0xd55ull}, {0x7eull, 0x820ull} }, // 2 x 6
    { {0x0ull, 0x1ull}, {0x3f00ull, 0x2040ull}, {0x0ull, 0x1ull}, {0xfeull, 0x2040ull} }, // 2 x 7
    { {0x8888ull, 0xd555ull}, {0xfe00ull, 0x8080ull}, {0x7776ull, 0xd555ull}, {0x1feull, 0x8080ull} } }, // 2 x 8
  { { {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull} }, // 3 x 0
    { {0x0ull, 0x7ull}, {0x0ull, 0x7ull}, {0x6ull, 0x7ull}, {0x6ull, 0x7ull} }, // 3 x 1
    { {0x30ull, 0x3bull}, {0x0ull, 0x1ull}, {0xeull, 0x3bull}, {0x0ull, 0x1ull} }, // 3 x 2
    { {0x188ull, 0x1caull}, {0x188ull, 0x135ull}, {0x76ull, 0x1caull}, {0x76ull, 0x135ull} }, // 3 x 3
    { {0x708ull, 0xa8aull}, {0x0ull, 0x1ull}, {0x8f6ull, 0xa8aull}, {0x0ull, 0x1ull} }, // 3 x 4
    { {0x6230ull, 0x729bull}, {0x3e20ull, 0x68d4ull}, {0x1dceull, 0x729bull}, {0x41deull, 0x68d4ull} }, // 3 x 5
    { {0x30c30ull, 0x3b6dbull}, {0x0ull, 0x1ull}, {0xf3ceull, 0x3b6dbull}, {0x0ull, 0x1ull} }, // 3 x 6
    { {0x188c30ull, 0x1ca6dbull}, {0x1be208ull, 0x128d45ull}, {0x773ceull, 0x1ca6dbull}, {0x41df6ull, 0x128d45ull} }, // 3 x 7
    { {0xc30c30ull, 0xedb6dbull}, {0x0ull, 0x1ull}, {0x3cf3ceull, 0xedb6dbull}, {0x0ull, 0x1ull} } }, // 3 x 8
  { { {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull} }, // 4 x 0
    { {0x0ull, 0xfull}, {0x0ull, 0xfull}, {0xeull, 0xfull}, {0xeull, 0xfull} }, // 4 x 1
    { {0xe0ull, 0xf7ull}, {0x88ull, 0xaaull}, {0x1eull, 0xf7ull}, {0x76ull, 0xaaull} }, // 4 x 2
    { {0x0ull, 0x1ull}, {0x708ull, 0xd75ull}, {0x0ull, 0x1ull}, {0x8f6ull, 0xd75ull} }, // 4 x 3
    { {0x7888ull, 0xad5aull}, {0x7888ull, 0xd2a5ull}, {0x8776ull, 0xad5aull}, {0x8776ull, 0xd2a5ull} }, // 4 x 4
    { {0x0ull, 0x1ull}, {0x7c308ull, 0xd1245ull}, {0x0ull, 0x1ull}, {0x83cf6ull, 0xd1245ull} }, // 4 x 5
    { {0x1f8888ull, 0x88d55aull}, {0x778888ull, 0xd52a55ull}, {0xe07776ull, 0x88d55aull}, {0x887776ull, 0xd52a55ull} }, // 4 x 6
    { {0x0ull, 0x1ull}, {0x77c3088ull, 0xd512455ull}, {0x0ull, 0x1ull}, {0x883cf76ull, 0xd512455ull} }, // 4 x 7
    { {0x78887888ull, 0xad5a2d5aull}, {0x77788888ull, 0xd552a555ull}, {0x87778776ull, 0xad5a2d5aull}, {0x88877776ull, 0xd552a555ull} } }, // 4 x 8
  { { {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull} }, // 5 x 0
    { {0x0ull, 0x1full}, {0x0ull, 0x1full}, {0x1eull, 0x1full}, {0x1eull, 0x1full} }, // 5 x 1
    { {0x3c0ull, 0x3efull}, {0x0ull, 0x1ull}, {0x3eull, 0x3efull}, {0x0ull, 0x1ull} }, // 5 x 2
    { {0x3e20ull, 0x572bull}, {0x6230ull, 0x4d64ull}, {0x41deull, 0x572bull}, {0x1dceull, 0x4d64ull} }, // 5 x 3
    { {0x7c308ull, 0xaedbaull}, {0x0ull, 0x1ull}, {0x83cf6ull, 0xaedbaull}, {0x0ull, 0x1ull} }, // 5 x 4
    { {0x7e2308ull, 0x12729baull}, {0x7e2308ull, 0x1d8d645ull}, {0x181dcf6ull, 0x12729baull}, {0x181dcf6ull, 0x1d8d645ull} }, // 5 x 5
    { {0x7f0c308ull, 0x223b6dbaull}, {0x0ull, 0x1ull}, {0x380f3cf6ull, 0x223b6dbaull}, {0x0ull, 0x1ull} }, // 5 x 6
    { {0x1f88c30e0ull, 0x49ca6db88ull}, {0x1e7e23088ull, 0x76d8d6455ull}, {0x60773cf1eull, 0x49ca6db88ull}, {0x6181dcf76ull, 0x76d8d6455ull} }, // 5 x 7
    { {0x7c3087c308ull, 0xaedba2edbaull}, {0x0ull, 0x1ull}, {0x83cf783cf6ull, 0xaedba2edbaull}, {0x0ull, 0x1ull} } }, // 5 x 8
  { { {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull} }, // 6 x 0
    { {0x0ull, 0x3full}, {0x0ull, 0x3full}, {0x3eull, 0x3full}, {0x3eull, 0x3full} }, // 6 x 1
    { {0xf80ull, 0xfdfull}, {0x888ull, 0xaaaull}, {0x7eull, 0xfdfull}, {0x776ull, 0xaaaull} }, // 6 x 2
    { {0x0ull, 0x1ull}, {0x30c30ull, 0x24924ull}, {0x0ull, 0x1ull}, {0xf3ceull, 0x24924ull} }, // 6 x 3
    { {0x778888ull, 0xaad5aaull}, {0x1f8888ull, 0xf72aa5ull}, {0x887776ull, 0xaad5aaull}, {0xe07776ull, 0xf72aa5ull} }, // 6 x 4
    { {0x0ull, 0x1ull}, {0x7f0c308ull, 0x3dc49245ull}, {0x0ull, 0x1ull}, {0x380f3cf6ull, 0x3dc49245ull} }, // 6 x 5
    { {0x1f7888e08ull, 0x88ad5a77aull}, {0x1f7888e08ull, 0xf752a5885ull}, {0xe087771f6ull, 0x88ad5a77aull}, {0xe087771f6ull, 0xf752a5885ull} }, // 6 x 6
    { {0x0ull, 0x1ull}, {0x21ddf0c3088ull, 0x2b568492455ull}, {0x0ull, 0x1ull}, {0x1e220f3cf76ull, 0x2b568492455ull} }, // 6 x 7
    { {0x877788887888ull, 0xd2a5d555d2a5ull}, {0x87777888e088ull, 0xad5a52a58855ull}, {0x788877778776ull, 0xd2a5d555d2a5ull}, {0x788887771f76ull, 0xad5a52a58855ull} } }, // 6 x 8
  { { {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull} }, // 7 x 0
    { {0x0ull, 0x7full}, {0x0ull, 0x7full}, {0x7eull, 0x7full}, {0x7eull, 0x7full} }, // 7 x 1
    { {0x3f00ull, 0x3fbfull}, {0x0ull, 0x1ull}, {0xfeull, 0x3fbfull}, {0x0ull, 0x1ull} }, // 7 x 2
    { {0x1be208ull, 0x1d72baull}, {0x188c30ull, 0x135924ull}, {0x41df6ull, 0x1d72baull}, {0x773ceull, 0x135924ull} }, // 7 x 3
    { {0x77c3088ull, 0xaaedbaaull}, {0x0ull, 0x1ull}, {0x883cf76ull, 0xaaedbaaull}, {0x0ull, 0x1ull} }, // 7 x 4
    { {0x1e7e23088ull, 0x492729baaull}, {0x1f88c30e0ull, 0x763592477ull}, {0x6181dcf76ull, 0x492729baaull}, {0x60773cf1eull, 0x763592477ull} }, // 7 x 5
    { {0x21ddf0c3088ull, 0x34a97b6dbaaull}, {0x0ull, 0x1ull}, {0x1e220f3cf76ull, 0x34a97b6dbaaull}, {0x0ull, 0x1ull} }, // 7 x 6
    { {0x79f88c307888ull, 0x1249ca6dbd2a5ull}, {0x79f88c307888ull, 0x1db6359242d5aull}, {0x1860773cf8776ull, 0x1249ca6dbd2a5ull}, {0x1860773cf8776ull, 0x1db6359242d5aull} }, // 7 x 7
    { {0x8777c30c307888ull, 0xd2a5edb6dbd2a5ull}, {0x0ull, 0x1ull}, {0x78883cf3cf8776ull, 0xd2a5edb6dbd2a5ull}, {0x0ull, 0x1ull} } }, // 7 x 8
  { { {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull}, {0x0ull, 0x1ull} }, // 8 x 0
    { {0x0ull, 0xffull}, {0x0ull, 0xffull}, {0xfeull, 0xffull}, {0xfeull, 0xffull} }, // 8 x 1
    { {0xfe00ull, 0xff7full}, {0x8888ull, 0xaaaaull}, {0x1feull, 0xff7full}, {0x7776ull, 0xaaaaull} }, // 8 x 2
    { {0x0ull, 0x1ull}, {0xc30c30ull, 0x924924ull}, {0x0ull, 0x1ull}, {0x3cf3ceull, 0x924924ull} }, // 8 x 3
    { {0x77788888ull, 0xaaad5aaaull}, {0x78887888ull, 0xd2a5d2a5ull}, {0x88877776ull, 0xaaad5aaaull}, {0x87778776ull, 0xd2a5d2a5ull} }, // 8 x 4
    { {0x0ull, 0x1ull}, {0x7c3087c308ull, 0xd1245d1245ull}, {0x0ull, 0x1ull}, {0x83cf783cf6ull, 0xd1245d1245ull} }, // 8 x 5
    { {0x87777888e088ull, 0xd2a5ad5a77aaull}, {0x877788887888ull, 0xad5a2aaa2d5aull}, {0x788887771f76ull, 0xd2a5ad5a77aaull}, {0x788877778776ull, 0xad5a2aaa2d5aull} }, // 8 x 6
    { {0x0ull, 0x1ull}, {0x8777c30c307888ull, 0xad5a1249242d5aull}, {0x0ull, 0x1ull}, {0x78883cf3cf8776ull, 0xad5a1249242d5aull} }, // 8 x 7
    { {0x8777788878887888ull, 0xd2a5ad5a2d5ad2a5ull}, {0x8777788878887888ull, 0xad5a52a5d2a52d5aull}, {0x7888877787778776ull, 0xd2a5ad5a2d5ad2a5ull}, {0x7888877787778776ull, 0xad5a52a5d2a52d5aull} } }// 8 x 8
} ;

#define FUR_HILBERT_FOR(i,j,imin,imax,jmin,jmax) {\
    int HILLOOP_imin = (imin);\
    int HILLOOP_imax = (imax);\
    int HILLOOP_jmin = (jmin);\
    int HILLOOP_jmax = (jmax);\
    (i) = HILLOOP_imin;\
    (j) = HILLOOP_jmin;\
    int HILLOOP_idiff = HILLOOP_imax - HILLOOP_imin;\
    int HILLOOP_jdiff = HILLOOP_jmax - HILLOOP_jmin;\
    if (HILLOOP_idiff > 0 && HILLOOP_jdiff > 0) {\
        int HILLOOP_iceil = HILLOOP_idiff - 1;\
        HILLOOP_iceil |= HILLOOP_iceil >> 1;\
        HILLOOP_iceil |= HILLOOP_iceil >> 2;\
        HILLOOP_iceil |= HILLOOP_iceil >> 4;\
        HILLOOP_iceil |= HILLOOP_iceil >> 8;\
        HILLOOP_iceil |= HILLOOP_iceil >> 16;\
        HILLOOP_iceil++;\
        if (HILLOOP_iceil < 8)\
            HILLOOP_iceil = 8;\
        int HILLOOP_jceil = HILLOOP_jdiff - 1;\
        HILLOOP_jceil |= HILLOOP_jceil >> 1;\
        HILLOOP_jceil |= HILLOOP_jceil >> 2;\
        HILLOOP_jceil |= HILLOOP_jceil >> 4;\
        HILLOOP_jceil |= HILLOOP_jceil >> 8;\
        HILLOOP_jceil |= HILLOOP_jceil >> 16;\
        HILLOOP_jceil++;\
        if (HILLOOP_jceil < 8)\
            HILLOOP_jceil = 8;\
        while ((i) < HILLOOP_imax && (j) < HILLOOP_jmax) {\
            int HILLOOP_icur, HILLOOP_jcur, HILLOOP_c, HILLOOP_x, HILLOOP_base, HILLOOP_icase, HILLOOP_jcase;\
            unsigned long long HILLOOP_stop, HILLOOP_hilbert = 0ull;\
            if (HILLOOP_idiff > HILLOOP_jdiff) {\
                HILLOOP_jcur = HILLOOP_jdiff;\
                HILLOOP_icur = HILLOOP_imax - (i);\
                HILLOOP_base = HILLOOP_jceil / 8;\
                HILLOOP_stop = HILLOOP_base * HILLOOP_base;\
                if (HILLOOP_icur >= 2 * HILLOOP_jceil) {\
                    HILLOOP_icur = HILLOOP_jceil;\
                    HILLOOP_c = 3;\
                    HILLOOP_icase = 0;\
                    HILLOOP_jcase = HILLOOP_jcur & 1;\
                } else if (HILLOOP_icur > HILLOOP_jceil) {\
                    HILLOOP_icur = (HILLOOP_icur + 3) / 4 * 2;\
                    HILLOOP_c = 3;\
                    HILLOOP_icase = 0;\
                    HILLOOP_jcase = HILLOOP_jcur & 1;\
                } else {\
                    HILLOOP_jcase = HILLOOP_jcur & 1;\
                    HILLOOP_icase = HILLOOP_icur & 1;\
                    HILLOOP_c = 3 - (HILLOOP_icase & ~HILLOOP_jcase);\
                    HILLOOP_icase += HILLOOP_icase & HILLOOP_jcase;\
                }\
            } else {\
                HILLOOP_icur = HILLOOP_idiff;\
                HILLOOP_jcur = HILLOOP_jmax - (j);\
                HILLOOP_base = HILLOOP_iceil / 8;\
                HILLOOP_stop = HILLOOP_base * HILLOOP_base;\
                if (HILLOOP_jcur >= 2 * HILLOOP_iceil) {\
                    HILLOOP_jcur = HILLOOP_iceil;\
                    HILLOOP_c = 2;\
                    HILLOOP_jcase = 0;\
                    HILLOOP_icase = HILLOOP_icur & 1;\
                } else if (HILLOOP_jcur > HILLOOP_iceil) {\
                    HILLOOP_jcur = (HILLOOP_jcur + 3) / 4 * 2;\
                    HILLOOP_c = 2;\
                    HILLOOP_jcase = 0;\
                    HILLOOP_icase = HILLOOP_icur & 1;\
                } else {\
                    HILLOOP_jcase = HILLOOP_jcur & 1;\
                    HILLOOP_icase = HILLOOP_icur & 1;\
                    HILLOOP_c = 2 + (HILLOOP_jcase & ~HILLOOP_icase);\
                    HILLOOP_jcase += HILLOOP_icase & HILLOOP_jcase;\
                }\
            }\
            int HILLOOP_i57 = 5 + 2 * (HILLOOP_icur > HILLOOP_base * 6);\
            if(HILLOOP_icur<6) HILLOOP_i57 = HILLOOP_icur ;\
            int HILLOOP_j57 = 5 + 2 * (HILLOOP_jcur > HILLOOP_base * 6);\
            if(HILLOOP_jcur<6) HILLOOP_j57 = HILLOOP_jcur ;\
            int HILLOOP_isize, HILLOOP_jsize;\
            HILLOOP_c ^= ((HILLOOP_base & 0x55555555) == 0) ;\
	    unsigned char *HILLOOP_P = (unsigned char*)malloc(sizeof(unsigned char));\
	    unsigned char *HILLOOP_A = (unsigned char*)malloc(sizeof(unsigned char));\
	    HILLOOP_P[0] = HILLOOP_c ;\
	    HILLOOP_A[0] = 1 ;\
            int HILLOOP_L = 0;\
            int HILLOOP_B = HILLOOP_base;\
            while (HILLOOP_B >>= 1) { ++HILLOOP_L; }\
    	    if(HILLOOP_L > 0){\
            	unsigned char HILLOOP_S1, HILLOOP_S2, HILLOOP_S3;\
                unsigned char HILLOOP_O = 64;\
                unsigned char HILLOOP_E = 0;\
            	HILLOOP_P = (unsigned char*)malloc(sizeof(char) * N_CHARS(HILLOOP_L));\
	        if(HILLOOP_c == 3) {\
		       	HILLOOP_S1 = 192;\
			HILLOOP_S2 = 128;\
			HILLOOP_S3 = 64;\
			HILLOOP_P[0] = 27;/*27*/\
		}\
		else if(HILLOOP_c == 2) {\
			HILLOOP_S1 = 128;\
		   	HILLOOP_S2 = 192;\
			HILLOOP_S3 = 0;\
			HILLOOP_P[0] = 14;/*14*/\
		}\
                HILLOOP_A = (unsigned char*)malloc(sizeof(char) * N_CHARS(HILLOOP_L));\
                HILLOOP_A[0] = 1;\
            	for(int l=1; l < HILLOOP_L; l++){\
        		int ceil = N_CHARS(l) - 1;\
			int offset_q2 = N_CHARS(l);\
			int offset_q3 = N_CHARS(l) * 2;\
			int offset_q4 = N_CHARS(l) * 3;\
			for(int c=0; c < ceil; c++){\
				HILLOOP_P[c + offset_q2] = HILLOOP_P[c] ^ XOR1111;\
				HILLOOP_P[c + offset_q3] = HILLOOP_P[c] ^ XOR1111;\
				HILLOOP_P[c + offset_q4] = HILLOOP_P[c] ^ XOR2222;\
                	        HILLOOP_A[c + offset_q2] = HILLOOP_A[c];\
                	        HILLOOP_A[c + offset_q3] = HILLOOP_A[c];\
                       		HILLOOP_A[c + offset_q4] = HILLOOP_A[c];\
			}\
                    	HILLOOP_P[ceil + offset_q2] = HILLOOP_P[ceil] ^ XOR0111;\
                    	HILLOOP_P[ceil + offset_q3] = HILLOOP_P[ceil] ^ XOR0111;\
                   	HILLOOP_P[ceil + offset_q4] = HILLOOP_P[ceil] ^ XOR0222;\
                    	HILLOOP_A[ceil + offset_q2] = HILLOOP_A[ceil];\
                    	HILLOOP_A[ceil + offset_q3] = HILLOOP_A[ceil];\
                    	HILLOOP_A[ceil + offset_q4] = HILLOOP_A[ceil];\
                    	CONCAT_STP(HILLOOP_P, HILLOOP_S1^=64, offset_q2-1);\
                    	CONCAT_STP(HILLOOP_P, HILLOOP_S2^=64, offset_q3-1);\
                    	CONCAT_STP(HILLOOP_P, HILLOOP_S3^=64, offset_q4-1);\
                    	CONCAT_STP(HILLOOP_A, HILLOOP_O^=64, offset_q2-1);\
                    	CONCAT_STP(HILLOOP_A, HILLOOP_E^=64, offset_q3-1);\
                    	CONCAT_STP(HILLOOP_A, HILLOOP_E, offset_q4-1);\
		}\
		CONCAT_STP(HILLOOP_P,HILLOOP_S1^64,(N_CHARS(HILLOOP_L)-1));\
                CONCAT_STP(HILLOOP_A,HILLOOP_O^64,(N_CHARS(HILLOOP_L)-1));\
	    }\
            int HILLOOP_I = 0;\
            int HILLOOP_J = 0;\
            unsigned char HILLOOP_C;\
            unsigned char HILLOOP_X;\
            while (HILLOOP_hilbert < HILLOOP_stop) {\
                if (HILLOOP_icase)\
                    if (HILLOOP_icase == 2) {\
                        int HILLOOP_v = HILLOOP_base - 1 - HILLOOP_J;\
                        HILLOOP_v |= HILLOOP_v >> 1;\
                        HILLOOP_v |= HILLOOP_v >> 2;\
                        HILLOOP_v |= HILLOOP_v >> 4;\
                        HILLOOP_v |= HILLOOP_v >> 8;\
                        HILLOOP_v |= HILLOOP_v >> 16;\
                        HILLOOP_v = (HILLOOP_v + 1) / 2;\
                        HILLOOP_isize = (HILLOOP_I == HILLOOP_v ? HILLOOP_i57 : (HILLOOP_I < HILLOOP_v ?\
                                (HILLOOP_I + 1) * (HILLOOP_icur-HILLOOP_i57) / (HILLOOP_base - 1) / 2 * 2\
                                - HILLOOP_I * (HILLOOP_icur - HILLOOP_i57) / (HILLOOP_base - 1) / 2 * 2 :\
                                HILLOOP_I * (HILLOOP_icur - HILLOOP_i57) / (HILLOOP_base - 1) / 2 * 2\
                                - (HILLOOP_I - 1) * (HILLOOP_icur - HILLOOP_i57) / (HILLOOP_base - 1) / 2 * 2));\
                    } else HILLOOP_isize = HILLOOP_I == HILLOOP_base - 1 ? HILLOOP_i57 :\
                            (HILLOOP_I + 1) * (HILLOOP_icur - HILLOOP_i57) / (HILLOOP_base - 1) / 2 * 2\
                        - HILLOOP_I * (HILLOOP_icur - HILLOOP_i57) / (HILLOOP_base - 1) / 2 * 2;\
                else HILLOOP_isize = (HILLOOP_I + 1) * HILLOOP_icur / HILLOOP_base / 2 * 2\
                        - HILLOOP_I * HILLOOP_icur / HILLOOP_base / 2 * 2;\
                if (HILLOOP_jcase)\
                    if (HILLOOP_jcase == 2) {\
                        int HILLOOP_v = HILLOOP_base - 1 - HILLOOP_I;\
                        HILLOOP_v |= HILLOOP_v >> 1;\
                        HILLOOP_v |= HILLOOP_v >> 2;\
                        HILLOOP_v |= HILLOOP_v >> 4;\
                        HILLOOP_v |= HILLOOP_v >> 8;\
                        HILLOOP_v |= HILLOOP_v >> 16;\
                        HILLOOP_v = (HILLOOP_v + 1) / 2;\
                        HILLOOP_jsize = (HILLOOP_J == HILLOOP_v ? HILLOOP_j57 : (HILLOOP_J < HILLOOP_v ?\
                                (HILLOOP_J + 1) * (HILLOOP_jcur-HILLOOP_j57) / (HILLOOP_base - 1) / 2 * 2\
                                - HILLOOP_J * (HILLOOP_jcur - HILLOOP_j57) / (HILLOOP_base - 1) / 2 * 2 :\
                                HILLOOP_J * (HILLOOP_jcur - HILLOOP_j57) / (HILLOOP_base - 1) / 2 * 2\
                                - (HILLOOP_J - 1) * (HILLOOP_jcur - HILLOOP_j57) / (HILLOOP_base - 1) / 2 * 2));\
                    } else HILLOOP_jsize = HILLOOP_J == HILLOOP_base - 1 ? HILLOOP_j57 :\
                            (HILLOOP_J + 1) * (HILLOOP_jcur - HILLOOP_j57) / (HILLOOP_base - 1) / 2 * 2\
                        - HILLOOP_J * (HILLOOP_jcur - HILLOOP_j57) / (HILLOOP_base - 1) / 2 * 2;\
                else HILLOOP_jsize = (HILLOOP_J + 1) * HILLOOP_jcur / HILLOOP_base / 2 * 2\
                        - HILLOOP_J * HILLOOP_jcur / HILLOOP_base / 2 * 2;\
                unsigned long long HILLOOP_nanoH = HILLOOP_nanoprog[HILLOOP_isize][HILLOOP_jsize][HILLOOP_c][0] ;\
                unsigned long long HILLOOP_nanoL = HILLOOP_nanoprog[HILLOOP_isize][HILLOOP_jsize][HILLOOP_c][1] ;\
                for(;;){

#define FUR_HILBERT_END(i,j)\
                    if(HILLOOP_nanoL == 1)\
                        break;\
                    int HILLOOP_d = HILLOOP_nanoL & 1 | HILLOOP_nanoH & 2 ;\
                    (i) += (HILLOOP_d - 2) % 2 ;\
                    (j) += (HILLOOP_d - 1) % 2 ;\
                    HILLOOP_nanoL /= 2 ;\
                    HILLOOP_nanoH /= 2 ;\
                }\
		if((HILLOOP_hilbert % 4) == 0){\
                	HILLOOP_C = HILLOOP_P[(HILLOOP_hilbert / 4)];\
                        HILLOOP_X = HILLOOP_A[(HILLOOP_hilbert / 4)];\
                }\
    		HILLOOP_c = HILLOOP_C % 4;\
    		HILLOOP_C = HILLOOP_C / 4;\
                HILLOOP_x = HILLOOP_X % 4;\
                HILLOOP_X = HILLOOP_X / 4;\
		HILLOOP_hilbert++;\
                HILLOOP_I += (HILLOOP_c - 2) % 2 ;\
                (i) += (HILLOOP_c - 2) % 2 ;\
                HILLOOP_J += (HILLOOP_c - 1) % 2 ;\
	        (j) += (HILLOOP_c - 1) % 2 ;\
	        HILLOOP_c ^= HILLOOP_x;\
            }\
        }\
    }\
}

#endif	/* FURHILBERT_H */

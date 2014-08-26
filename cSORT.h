#ifndef _CDLT_H_
#define _CDLT_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

//================================================================================================
#define STREAM_OUT								0													//=0: SERIE      stream out merged keys into single bank
																														//=1: PARALLEL   stream out merged keys into 4 banks		
#define STREAM_IN									0													//=0: SERIE      stream in merged keys into single bank
																														//=1: PARALLEL   stream in merged keys into 4 banks

#define KEY_SIZE 									4
#define LOG_NUM_KEY								10
#define NUM_LMBANK								64
#define ME_SIZE										4													// 4-word buffer
#define NUM_ME										16

#define NUM_KEY 									(1<<LOG_NUM_KEY)
#define NUM_SORTED_BLOCK          (NUM_KEY/ME_SIZE)
#define NKEYS_PER_LMBANK					(NUM_KEY/NUM_LMBANK)
#define LMBANK_SIZE								(16*1024)									// 16K-word local memory
#define LM_SIZE                   (NUM_LMBANK*LMBANK_SIZE)	// size in word
//================================================================================================
int *lm_mem;
int *mbuf;


// list must be 16 aligned for now, length is assumed to be 2^n
	void merge_sort      (int *buffer, int *list,  int length);
	void merge_sort_rev  (int *buffer, int *list,  int length);
	void merge_sort_merge(int *output, int *input, int length);


#endif /**** End of header ***/


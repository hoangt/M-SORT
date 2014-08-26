#include <time.h>

#include "cDEBUG.h"
#include "cSORT.h"
#include "cDLT.h"

//==========================================================================================================
int main()
{
	int 	i, j, iter;
	int 	*lm_src_addr[64];
	int 	*lm_dst_addr[64];
	int		*lm_src1, *lm_src2;
	int		*lm_dst1, *lm_dst2;
	int   *basePtr;
	int		nelem, stride, fsize, desc;

	char  msg[100];
	int   BATCH = 1;

	mbuf = malloc(ME_SIZE*sizeof(int));	

	//lm_src_addr =  malloc(64*KEY_SIZE);
	//lm_dst_addr =  malloc(64*KEY_SIZE);

	srand(time(NULL));

	lm_mem 	= malloc(LM_SIZE*KEY_SIZE);
	lm_src1 = lm_mem;
	lm_src2 = lm_src1 + (LM_SIZE>>2);
	lm_dst1 = lm_src2 + (LM_SIZE>>2);
	lm_dst2 = lm_dst1 + (LM_SIZE>>2);

for (iter=0; iter < BATCH; iter++) 
{
	//*** Initialize data ***//
		for (i=0; i< NUM_KEY; i++)
			*(lm_mem + i) = rand()%2000;

	//************************************************
	// BLOCK-SORT (4 keys/block)
	//************************************************
		for (i=0; i< NUM_KEY; i+=64)
		{
				//vsort64(lm_mem+i);
				//for (j=0; j<64; j+=4)
				//	check_sort(lm_mem+i+j, 4);
		}

		//printf_ptr("First  64 keys:", lm_mem,    64);
		//printf_ptr("Second 64 keys:", lm_mem+64, 64);
	//************************************************

	//************************************************
	// MERGE-SORT (4 keys/block)
	//************************************************
		//=== Test single merge
		int nsort = 2;

		//printf_ptr("Input ", lm_src1, (nsort+2)*ME_SIZE);

    test_merge_sort(5);
		//test_bitonic_sort_2x8keys(lm_src1);
}

	return 0;
}

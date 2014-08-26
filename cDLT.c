#include "cDLT.h"
#include <time.h>

//=======================================================================================================================================
// 4-key block transposes
//=======================================================================================================================================
int form_dlt_descriptor(unsigned int nelem, unsigned int stride, unsigned int fsize)
{
		return ((nelem & 0x0000003f) << 19) | (stride << 7) | fsize;
}

//=========================================================================================
void gather(int *dst, int *src, unsigned int desc)
{
		int i, j;

		int fsize 	= (desc      ) & 0x0000007f;
		int stride 	= (desc >>  7) & 0x00000fff;
		int nelem   = (desc >> 19);

		//printf("nelem=%d, stride=%d, fsize=%d, desc=%d\n", nelem, stride, fsize, desc);
		//printf("\nDEBUG --- desc=%4d, nelem=%4d, stride=%4d, fsize=%4d\n", desc, nelem, stride/fsize, fsize);
		for (i=0; i<nelem; i++)
		{
				char *src1 = ((char *) src) + i*stride*fsize;
				char *dst1 = ((char *) dst) + i*fsize;		

				memcpy(dst1, src1, fsize);
				//printf("i=%d, desc=%d, stride=%d, fsize=%d, nelem=%d, %d, %d\n", i, desc, stride, fsize, nelem, *(src + i*stride*fsize), *(dst + i*fsize) );
		}
}


//=========================================================================================
void scatter(int *dst, int *src, unsigned int desc)
{
		int i,j;

		int fsize 	= (desc      ) & 0x0000007f;
		int stride 	= (desc >>  7) & 0x00000fff;
		int nelem   = (desc >> 19);

		for (i=0; i<nelem; i++)
		{			
				int *src1 = src + i*fsize*fsize;
				int *dst1 = dst + i*stride;
				memcpy(dst1, src1, fsize);

				//for (j=0; j< fsize; j++) dst[j]=src[j];
		}
}

//=========================================================================================
/*
int main()
{
		
	int desc, fsize, stride, nelem, i, j;

	srand(time(NULL));

	for (i=0; i<10; i++) 
	{
		int a = rand()%64;
		int b = rand()%64;
		int c = rand()%64;
		desc  = form_dlt_descriptor(a, b, c);

		int fsize 	= (desc      ) & 0x0000007f;
		int stride 	= (desc >>  7) & 0x00000fff;
		int nelem   = (desc >> 19);

		printf("\nDEBUG --- desc=%4d, nelem=%4d (%4d), stride=%4d (%4d), fsize=%4d (%4d)\n", desc, nelem, a, stride, b, fsize, c);
	}

	int size = 32;
	int *src = malloc(size * size * sizeof (int));
	int *dst = malloc(size * size * sizeof (int));

	for (i=0; i< size; i++)
		for (j=0; j< size; j++)
		{
			src[i*size+j] = i+1;
			dst[i*size+j] = 0;
		}

	printf("INPUT: \n");
	for (i=0; i< 32; i++) {
		for (j=0; j< 32; j++) printf("%2d, ", src[i*size+j]);
		printf("\n");
	}
			
	nelem 	= size;
	stride 	= size;
	fsize   = 4;

	desc  = form_dlt_descriptor(nelem, stride, fsize);
		gather((int *) dst, (int *) src, desc);

	desc  = form_dlt_descriptor(nelem-1, size, fsize);
		scatter((int *) dst+size*fsize, (int *) dst+fsize, desc);

	printf("\n\nOUTPUT: \n");
	for (i=0; i< 32; i++) {
		for (j=0; j< 32; j++) printf("%2d, ", dst[i*size+j]);
		printf("\n");
	}

	return 0;
}
*/

#include "cSORT.h"

//==========================================================================================================
void write2lm(int *out, int *in)
{
		out[0] = in[0]; out[1] = in[1]; out[2] = in[2]; out[3] = in[3];
}

//==========================================================================================================
void sort1x4(int *out, int *in)
{
		int *x0 = in;
		int *x1 = in+1;
		int *x2 = in+2;
		int *x3 = in+3;

		int m0_0 = *x1 >= *x0 ? *x0 : *x1;
		int m0_1 = *x1 >= *x0 ? *x1 : *x0;
		int m0_2 = *x3 >= *x2 ? *x2 : *x3;
		int m0_3 = *x3 >= *x2 ? *x3 : *x2;

		int m1_1 = m0_2 >= m0_0 ? m0_2 : m0_0;
		int m1_2 = m0_3 >= m0_1 ? m0_1 : m0_3;

		*(out  ) = m0_2 >= m0_0 ? m0_0 : m0_2;
		*(out+1) = m1_2 >= m1_1 ? m1_1 : m1_2;
		*(out+2) = m1_2 >= m1_1 ? m1_2 : m1_1;
		*(out+3) = m0_3 >= m0_1 ? m0_3 : m0_1;
}

//==========================================================================================================
void vsort16x4(int *out[], int *in[], int N)
{
	int i;
	int *tmp;

	assert(N >=0 && N <=16);

	for (i=0; i<N; i++)
		sort1x4(in[i], out[i]);
}

//==========================================================================================================
void sort4x4(int *out[], int *in[])						// sort 4x4 elements in parallel
{
		vsort16x4(in, out, 4);
}

//==========================================================================================================
void merge2x4(int *x, int *y)
{
		int m[4], n[4];

    m[0] = x[0] >= y[0] ? y[0] : x[0]; m[1] = x[0] >= y[0] ? x[0] : y[0];
    m[2] = x[2] >= y[2] ? y[2] : x[2]; m[3] = x[2] >= y[2] ? x[2] : y[2];
    n[0] = x[1] >= y[1] ? y[1] : x[1]; n[1] = x[1] >= y[1] ? x[1] : y[1];
    n[2] = x[3] >= y[3] ? y[3] : x[3]; n[3] = x[3] >= y[3] ? x[3] : y[3];

		x[1] = m[2] >= m[1] ? m[1] : m[2]; x[2] = m[2] >= m[1] ? m[2] : m[1]; x[3] = m[3];					
		y[1] = n[2] >= n[1] ? n[1] : n[2]; y[2] = n[2] >= n[1] ? n[2] : n[1]; y[3] = n[3];		

    m[1] = y[0] >= x[1] ? x[1] : y[0]; m[2] = y[0] >= x[1] ? y[0] : x[1]; m[3] = y[1] >= x[2] ? x[2] : y[1];
    n[0] = y[1] >= x[2] ? y[1] : x[2]; n[1] = y[2] >= x[3] ? x[3] : y[2]; n[2] = y[2] >= x[3] ? y[2] : x[3];

    x[0] = m[0]; x[1] = m[1];	x[2] = m[2]; x[3] = m[3];
		y[0] = n[0]; y[1] = n[1]; y[2] = n[2]; y[0] = n[0];					           
}

//==========================================================================================================
void merge4x4(int *x0, int *x1, int *x2, int *x3)
{

}

void vmerge16x4(int *out, int *in[], int N)
{
	assert(N >=0 && N <=16);

	int i;
	for (i=0; i<N; i++)
		merge2x4(in[i], out[i]);					           
}

//==========================================================================================================
void bisort2x8(int *out, int* in)				// TUNG: Kernel of sort (accelerator)
{

    int *x[4];

		x[0] = in   ;
		x[1] = in+ 4;
		x[2] = in+ 8;
		x[3] = in+12;

    //puts("\nsort4x4 INPUT:");
    //printf_ptr("x0: ", x0, 4); printf_ptr("x1: ", x1, 4); printf_ptr("x2: ", x2, 4); printf_ptr("x3: ", x3, 4); 
		//puts("--------------------------------------------\n");

		sort4x4(x, x);
    //puts("sort4x4 OUTPUT:");
    //printf_ptr("x0: ", x0, 4); printf_ptr("x1: ", x1, 4); printf_ptr("x2: ", x2, 4); printf_ptr("x3: ", x3, 4);
		//puts("--------------------------------------------\n");

    merge2x4(x[0], x[1]);
    merge2x4(x[2], x[3]);
    //puts("merge4 OUTPUT:");
		//printf_ptr("x0: ", x0, 4); printf_ptr("x1: ", x1, 4); printf_ptr("x2: ", x2, 4); printf_ptr("x3: ", x3, 4);
		//puts("--------------------------------------------\n");
}


//==========================================================================================================
/* merge_sort_rev is expected to sort input and write output to output */
void merge_sort_rev(int *output, int *input, int length)
{
    int half = length >> 1;
    if (length == 16){
        bisort2x8(input, input);
    } else {
        merge_sort(output,        input,        half);
        merge_sort(output + half, input + half, half);
    }
    
    merge_sort_merge(output, input, length);
}

//==========================================================================================================
void merge_sort_merge(int *output, int *input, int length)
{
		int i;

    int half;
    int *halfptr;
    int *sentinelptr;

    half 				= length >> 1;
    halfptr 		= input + half;
    sentinelptr = input + length;

    int *list1  = input;
    int *list2  = halfptr;
		int *mebuf  = list2;
		
    merge2x4(list1, mebuf);
    
		write2lm(output, list1);

    list1  += 4;
    list2  += 4;
    output += 4;

    while(1) 
		{
			if (*list1 < *list2) 
			{
					printf("DEBUG --- *list1 < *list2\n");
		      merge2x4(list1, mebuf); write2lm(output, list1);
  	      list1 += 4; output += 4;

  	      if (list1 >= halfptr)
					{

							int N=(sentinelptr-list2) >> 2;		// do 4x4 merge
					    for (i=0; i < N; i++)
							{
					        merge2x4(list2, mebuf); write2lm(output, list2);
					        list2 += 4; output += 4;
						  }
							write2lm(output, mebuf);
							
							return;
					}

			//===============================
      } else {
					printf("DEBUG --- *list1 >= *list2\n");
  	      merge2x4(list2, mebuf); write2lm(output, list2);
  	      list2 += 4; output += 4;

  	      if (list2 >= sentinelptr)
					{
							int N=(halfptr-list1) >> 2;

					    for (i=0; i < N; i++)
							{
					        merge2x4(list1, mebuf); write2lm(output, list1);
					        list1 += 4; output += 4;
							}
							write2lm(output, mebuf);

							return;				
			    }
      }
    }

    return;
}

//==========================================================================================================
/* merge_sort is expected to sort input in place */
void merge_sort(int *output, int *input, int length)
{
    int half = length >> 1;
    if (length == 16){
        bisort2x8(output, input);
    } else {
        merge_sort_rev(output,        input,        half);
        merge_sort_rev(output + half, input + half, half);
    }
    merge_sort_merge(input, output, length);
}


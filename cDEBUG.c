#include "cSORT.h"
#include "cDEBUG.h"

//================================================================================================
void printf_ptr(char *msg, int *a, int N)
{
	int i;

	printf("\nDEBUG --- %s\n", msg);
	for (i=0; i<N; i++)
		#ifdef DBG
			printf("(%d, %4d) ", (unsigned int) (a+i), a[i]);
		#else
			printf("%4d, ", a[i]);
		#endif
	printf("\n");
}

//================================================================================================
void printf_array_ptr(char *msg, int *a[], int N)
{
	int i;

	printf("\nDEBUG --- %s\n", msg);
	for (i=0; i<N; i++)
		#ifdef DBG
			printf("(%d, %4d), ", (unsigned int) (a[i]), *a[i]);
		#else
			printf("%4d, ", *a[i]);
		#endif
	printf("\n");
}

//================================================================================================
int get_lm_addr(int lm_addr, int base_add)
{
	return ((lm_addr-base_add) >> 8) & 0x00003fff;
}

//================================================================================================
int get_bank_num(int lm_addr, int base_add)
{
	return ((lm_addr-base_add) >> 16);
}

//================================================================================================
void check_sort(int *lm_addr, int N)
{
	int i;

	for (i=0; i< N-1; i++)
		if ( *(lm_addr+i) > *(lm_addr+i+1) ) {
			printf_ptr("\nERROR --- WRONG order in this stream", lm_addr, i+1);
			assert(0);
		}
	//printf("\nINFOR --- Keys are sorted !!!\n");
}

//================================================================================================
void test_sort4x4(int *out[], int *in[])				// TEST: sort 4x4 elements in parallel
{
		printf_ptr("sort4x4 input X_0: ", in[0], 4);
		printf_ptr("sort4x4 input X_1: ", in[1], 4);
		printf_ptr("sort4x4 input X_2: ", in[2], 4);
		printf_ptr("sort4x4 input X_3: ", in[3], 4);

		sort4x4(out, in);

		printf_ptr("sort4x4 output X_0:", out[0], 4);
		printf_ptr("sort4x4 output X_1:", out[1], 4);
		printf_ptr("sort4x4 output X_2:", out[2], 4);
		printf_ptr("sort4x4 output X_3:", out[3], 4);
}

//================================================================================================
void test_merge2x4(int *x, int *y)
{
		printf_ptr("test_merge4 input X: ", x, 4);
		printf_ptr("test_merge4 input Y: ", y, 4);

		merge2x4(x, y);

		printf_ptr("test_merge4 output X:", x, 4);
		printf_ptr("test_merge4 output Y:", y, 4);
}

//================================================================================================
void test_bisort2x8(int *in)
{
    int i;

		printf_ptr("bitonic_sort_16key, first 8 keys input: ", in,   8);
		printf_ptr("bitonic_sort_16key, last  8 keys input: ", in+8, 8);

    bisort2x8(in, in);

		printf_ptr("bitonic_sort_16key, first 8 keys output:", in,   8);
		printf_ptr("bitonic_sort_16key, last  8 keys output:", in+8, 8);
}


//================================================================================================
void test_sort1x4(int *in)
{
		printf_ptr("Sort4 input: ", in, 4);

		sort1x4(in);

		printf_ptr("Sort4 output:", in, 4);
}

//================================================================================================
void test_vsort16x4(int *out[], int *in[], int N)
{
	int i;
	char msg[50];

	for (i=0; i<N; i++) 
	{
		sprintf(msg, "vsort16x4 input  X_%d", i); printf_ptr(msg,  in[i], 4);		

		sort1x4(out[i], in[i]);

		sprintf(msg, "vsort16x4 output X_%d", i); printf_ptr(msg, out[i], 4);
	}
}

//================================================================================================

void test_merge_sort(int num_exp)
{
    int *list;
    int *buffer;
    int num = 1 << num_exp;
    struct timeval start_time, end_time;
    
    //fprintf(stderr, "size: %d\n", num);
    //posix_memalign(&list,   16, sizeof(int) * num);
    //posix_memalign(&buffer, 16, sizeof(int) * num);

    //memset(list, 0, sizeof(int) * num);
    //memset(buffer, 0, sizeof(int) * num);

		list   = malloc(num*sizeof(int));
		buffer = malloc(num*sizeof(int));

    int i, j;
    srand(time(NULL));

	
	float run_time 	 = 0;
	int 	batch_size = 1;

	for (j=0; j<batch_size; j++)
	{
    fprintf(stderr, "input data generated.\n");
    for(i = 0;i < num;i++){
        list[i] = rand()%2000;
				//list[i] = num-i-1;
		    fprintf(stderr, "%4d, ", list[i]);
    }
    fprintf(stderr, "\n");
		
    
    gettimeofday(&start_time, NULL);
    	merge_sort(buffer, list, num);
    gettimeofday(&end_time, NULL);
    
    fprintf(stderr, "sorted.\n");
    for(i = 0;i < num - 1;i++){
        if (list[i] > list[i+1]){
			    for(i = 0;i < num;i++)
				    fprintf(stderr, "%4d, ", list[i]);

          printf("[%4d] %4d, [%4d] %4d: not sorted.\n", i, list[i], i+1, list[i+1]);
					assert(0);
        }
    }
    fprintf(stderr, "Data is sorted and CHECKED !!!\n");
    fprintf(stderr, "output sorted data.\n");
    for(i = 0;i < num;i++){
		    fprintf(stderr, "%4d, ", list[i]);
    }
    fprintf(stderr, "\n");
				
		float rtime = (double)(end_time.tv_sec - start_time.tv_sec) + (double)(end_time.tv_usec - start_time.tv_usec)/1000000;
    printf("Sorting time, batch=%d: %lf seconds\n", j, rtime);
		run_time += rtime;
		printf("**************************************\n");
	}

	printf("Average running time=%lf\n", run_time/batch_size);

}

//***********************************************************************************************
//***********************************************************************************************
//***********************************************************************************************
void orig_merge_sort_merge(int *output, int *input, int length)
{

    int half;
    int *halfptr;
    int *sentinelptr;

    half 				= length / 2;
    halfptr 		= input + half;
    sentinelptr = input + length;

    int *x, *y;
    int *list1 = input;
    int *list2 = halfptr;
    x = list1;
    y = list2;

    list1 += 4;
    list2 += 4;

    merge2x4(x, y);
    
		//_mm_storeu_ps(output, x);
			output[0] = x[0];	output[1] = x[1]; output[2] = x[2]; output[3] = x[3];
		
    output += 4;
    while(1){
        if (*list1 < *list2){
            //x = _mm_load_ps(list1);
							x[0] = list1[0]; x[1] = list1[1]; x[2] = list1[2]; x[3] = list1[3];

            list1 += 4;
            merge2x4(x, y);
  
	          //_mm_storeu_ps(output, x);
							output[0] = x[0];	output[1] = x[1]; output[2] = x[2]; output[3] = x[3];

            output += 4;
            if (list1 >= halfptr){
                goto nomore_in_list1;
            }
        } else {
            //x = _mm_load_ps(list2);
							x[0] = list2[0]; x[1] = list2[1]; x[2] = list2[2]; x[3] = list2[3];

            list2 += 4;
            merge2x4(x, y);

            //_mm_storeu_ps(output, x);
							output[0] = x[0];	output[1] = x[1]; output[2] = x[2]; output[3] = x[3];

            output += 4;
            if (list2 >= sentinelptr){
                goto nomore_in_list2;
            }
        }
    }

//******************
nomore_in_list1:
    while(list2 < sentinelptr){
        //x = _mm_load_ps(list2);
					x[0] = list2[0]; x[1] = list2[1]; x[2] = list2[2]; x[3] = list2[3];

        list2 += 4;
        merge2x4(x, y);

        //_mm_storeu_ps(output, x);
					output[0] = x[0];	output[1] = x[1]; output[2] = x[2]; output[3] = x[3];

        output += 4;
    }
    goto end;

//******************
nomore_in_list2:
    while(list1 < halfptr){
        //x = _mm_load_ps(list1);
					x[0] = list1[0]; x[1] = list1[1]; x[2] = list1[2]; x[3] = list1[3];

        list1 += 4;
        merge2x4(x, y);

        //_mm_storeu_ps(output, x);
					output[0] = x[0];	output[1] = x[1]; output[2] = x[2]; output[3] = x[3];

        output += 4;
    }

//******************
end:   
    //_mm_storeu_ps(output, y);
			output[0] = y[0];	output[1] = y[1]; output[2] = y[2]; output[3] = y[3];

    return;
}



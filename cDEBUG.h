#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//#define DBG  1

//====================================================================================================
// testing functions
	void test_sort1x4	  						(int *x);
	void test_merge2x4	 						(int *x,  int *y);

	void test_sort4x4								(int *out[], int *in[]);
	void test_merge2x4  						(int *x,  int *y);

	void test_vsort16x4							(int *out[], int *in[], int N);
	void test_vmerge16x4						(int *out[], int *in[], int N);

	void test_bisort2x8							(int *in);
	void test_merge_sort						(int num_exp);


	void check_sort									(int *lm_addr, int N);
	void printf_ptr									(char *msg, int *a, int N);
	void printf_array_ptr						(char *msg, int *a[], int N);
	int get_lm_addr									(int lm_addr, int base_add);
	int get_bank_num								(int lm_addr, int base_add);


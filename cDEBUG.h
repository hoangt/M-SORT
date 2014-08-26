#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//#define DBG  1

//====================================================================================================
// testing functions
	void test_sort4x4								(int *in);
	void test_vsort16								(int *in[], int N);
	void test_sort4x4								(int *in[]);
	void test_merge4	  						(int *x,  int *y);
	void test_bitonic_sort_2x8keys	(int *in);
	void test_merge_sort						(int num_exp);


	void check_sort									(int *lm_addr, int N);
	void printf_ptr									(char *msg, int *a, int N);
	void printf_array_ptr						(char *msg, int *a[], int N);
	int get_lm_addr									(int lm_addr, int base_add);
	int get_bank_num								(int lm_addr, int base_add);


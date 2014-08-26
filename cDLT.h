#ifndef _CDLT_H_
#define _CDLT_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef 	char   byte;

//================================================================================================
	int form_dlt_descriptor(unsigned int nelem, unsigned int stride, unsigned int fsize);

	void gather(int *dst, int *src, unsigned int desc);

	void scatter(int *dst, int *src, unsigned int desc);

#endif	/**** End of header ***/

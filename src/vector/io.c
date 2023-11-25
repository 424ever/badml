#include <stdio.h>

#include "error.h"
#include "vector.h"

int bml_vector_print(FILE *f, struct bml_vector *vec, const char *format)
{
	int    count;
	int    ret;
	size_t i;

	count = 0;

	for (i = 0; i < vec->size; ++i)
	{
		ret = fprintf(f, format, vec->buf[i]);
		if (ret < 0)
		{
			bml_error(__FUNCTION__, "printf");
			return -1;
		}
		count += ret;
		++count;
		(void) fputc('\n', f);
	}
	return count;
}

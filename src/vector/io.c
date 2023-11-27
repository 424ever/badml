#include <stdio.h>

#include "block.h"
#include "bml_vector.h"
#include "error.h"
#include "vector.h"

int bml_vector_print(FILE *f, const struct bml_vector *vec, const char *format)
{
	int    count;
	int    ret;
	size_t i;

	count = 0;

	for (i = 0; i < bml_vector_size(vec); ++i)
	{
		ret = fprintf(f, format, bml_block_must_get(vec->b, i));
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

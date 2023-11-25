#include <math.h>
#include <stddef.h>

#include "alloc.h"
#include "error.h"
#include "vector.h"

double bml_vector_dot_product(struct bml_vector *a, struct bml_vector *b)
{
	double sum;
	size_t i;

	if (a->size != b->size)
	{
		bml_error(__FUNCTION__, "different sizes");
		return NAN;
	}

	sum = 0.0;

	for (i = 0; i < a->size; ++i)
		sum += a->buf[i] * b->buf[i];

	return sum;
}

struct bml_vector *bml_vector_cross_product(struct bml_vector *a,
					    struct bml_vector *b)
{
	struct bml_vector *vec;

	if (a->size != 3)
	{
		bml_error(__FUNCTION__, "a's size is not 3");
		return NULL;
	}

	if (b->size != 3)
	{
		bml_error(__FUNCTION__, "b's size is not 3");
		return NULL;
	}

	vec = bml_vec_alloc_with_error(__FUNCTION__, 3);
	if (!vec)
		return NULL;

	vec->buf[0] = a->buf[1] * b->buf[2] - a->buf[2] * b->buf[1];
	vec->buf[1] = a->buf[2] * b->buf[0] - a->buf[0] * b->buf[2];
	vec->buf[2] = a->buf[0] * b->buf[1] - a->buf[1] * b->buf[0];

	return vec;
}

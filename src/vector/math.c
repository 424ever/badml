#include <math.h>
#include <stddef.h>

#include "block.h"
#include "bml_vector.h"
#include "error.h"
#include "vector.h"

double bml_vector_dot_product(const struct bml_vector *a,
			      const struct bml_vector *b)
{
	double sum;
	double d1;
	double d2;
	size_t i;

	if (bml_vector_size(a) != bml_vector_size(b))
	{
		bml_error(__FUNCTION__, "different sizes");
		return NAN;
	}

	sum = 0.0;

	for (i = 0; i < bml_vector_size(a); ++i)
	{
		d1 = bml_block_must_get(a->b, i);
		d2 = bml_block_must_get(b->b, i);
		sum += d1 * d2;
	}

	return sum;
}

struct bml_vector *bml_vector_cross_product(const struct bml_vector *a,
					    const struct bml_vector *b)
{
	struct bml_vector *vec;

	if (bml_vector_size(a) != 3)
	{
		bml_error(__FUNCTION__, "a's size is not 3");
		return NULL;
	}

	if (bml_vector_size(b) != 3)
	{
		bml_error(__FUNCTION__, "b's size is not 3");
		return NULL;
	}

	vec = bml_vec_alloc_with_error(__FUNCTION__, 3);
	if (!vec)
		return NULL;

	vec->b->data[0] =
	    a->b->data[1] * b->b->data[2] - a->b->data[2] * b->b->data[1];
	vec->b->data[1] =
	    a->b->data[2] * b->b->data[0] - a->b->data[0] * b->b->data[2];
	vec->b->data[2] =
	    a->b->data[0] * b->b->data[1] - a->b->data[1] * b->b->data[0];

	return vec;
}

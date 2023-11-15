#include <math.h>
#include <stddef.h>

#include "bml_error_int.h"
#include "bml_vector.h"
#include "bml_vector_int.h"

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

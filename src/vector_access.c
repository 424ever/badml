#include <math.h>

#include "vector.h"

size_t bml_vector_size(struct bml_vector *vec)
{
	return vec->size;
}

void bml_vector_set(struct bml_vector *vec, size_t i, double d)
{
	if (bml_vec_bounds_valid(vec, i, __FUNCTION__))
		vec->buf[i] = d;
}

double bml_vector_get(struct bml_vector *vec, size_t i)
{
	if (bml_vec_bounds_valid(vec, i, __FUNCTION__))
		return vec->buf[i];
	return NAN;
}

double *bml_vector_ptr(struct bml_vector *vec, size_t i)
{
	if (bml_vec_bounds_valid(vec, i, __FUNCTION__))
		return vec->buf + i;
	return NULL;
}

const double *bml_vector_const_ptr(struct bml_vector *vec, size_t i)
{
	return bml_vector_ptr(vec, i);
}

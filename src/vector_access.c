#include <math.h>

#include "error.h"
#include "vector.h"

typedef int(comparfn)(double, double, void *);

static int compare_exact(double a, double b, void *data)
{
	(void) data;
	return a == b;
}

static int compare_tol(double a, double b, void *data)
{
	double tol;

	tol = *((double *) data);
	return fabs(b - a) <= tol;
}

static int comp(comparfn *fn, struct bml_vector *a, struct bml_vector *b,
		void *data)
{
	size_t i;

	if (a->size != b->size)
		return 0;

	for (i = 0; i < a->size; ++i)
	{
		if (!fn(a->buf[i], b->buf[i], data))
			return 0;
	}

	return 1;
}

static int bml_vec_bounds_valid(struct bml_vector *vec, size_t i,
				const char *fn)
{
	if (i >= vec->size)
	{
		bml_error(fn, "out of bounds");
		return 0;
	}
	return 1;
}

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

int bml_vector_eq(struct bml_vector *a, struct bml_vector *b)
{
	return comp(&compare_exact, a, b, NULL);
}

int bml_vector_eq_tol(struct bml_vector *a, struct bml_vector *b, double tol)
{
	return comp(&compare_tol, a, b, &tol);
}

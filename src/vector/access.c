#include <math.h>

#include "block.h"
#include "bml_vector.h"
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

	if (bml_vector_size(a) != bml_vector_size(b))
		return 0;

	for (i = 0; i < bml_vector_size(a); ++i)
	{
		if (!fn(bml_vector_get(a, i), bml_vector_get(b, i), data))
			return 0;
	}

	return 1;
}

size_t bml_vector_size(struct bml_vector *vec)
{
	return vec->b->size;
}

void bml_vector_set(struct bml_vector *vec, size_t i, double d)
{
	bml_block_set(__FUNCTION__, vec->b, d, i);
}

double bml_vector_get(struct bml_vector *vec, size_t i)
{
	double d;

	if (!bml_block_get(__FUNCTION__, vec->b, &d, i))
		return NAN;

	return d;
}

double *bml_vector_ptr(struct bml_vector *vec, size_t i)
{
	return bml_block_ptr(__FUNCTION__, vec->b, i);
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

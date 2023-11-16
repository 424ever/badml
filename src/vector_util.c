#include <stdlib.h>
#include <string.h>

#include "alloc.h"
#include "error.h"
#include "vector.h"

int bml_vec_bounds_valid(struct bml_vector *vec, size_t i, const char *fn)
{
	if (i >= vec->size)
	{
		bml_error(fn, "out of bounds");
		return 0;
	}
	return 1;
}

struct bml_vector *bml_vec_alloc_with_error(const char *fn, size_t n)
{
	struct bml_vector *vec;

	vec = bml_alloc(fn, 1, sizeof(*vec));
	if (!vec)
		return NULL;

	vec->size   = n;
	vec->buf    = bml_alloc(fn, n, sizeof(*(vec->buf)));
	vec->owning = 1;

	if (!vec->buf)
	{
		free(vec);
		return NULL;
	}

	return vec;
}

struct bml_vector *bml_vec_alloc_with_backing(const char *fn, double *back,
					      size_t n)
{
	struct bml_vector *vec;

	vec = bml_alloc(fn, 1, sizeof(*vec));
	if (!vec)
		return NULL;

	vec->size   = n;
	vec->buf    = back;
	vec->owning = 0;

	return vec;
}

struct bml_vector *bml_vec_alloc_from_backing_copy(const char	*fn,
						   const double *back, size_t n)
{
	struct bml_vector *vec;

	vec = bml_vec_alloc_with_error(fn, n);
	if (!vec)
		return NULL;
	memcpy(vec->buf, back, n * sizeof(*back)); /* NOLINT */

	return vec;
}
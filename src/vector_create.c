#include <string.h>

#include "alloc.h"
#include "error.h"
#include "vector.h"

static struct bml_vector *bml_vec_alloc_with_error(const char *fn, size_t n)
{
	struct bml_vector *vec;

	if (!n)
	{
		bml_error(fn, "size is 0");
		return NULL;
	}

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

static struct bml_vector *bml_vec_alloc_with_backing(const char *fn,
						     double *back, size_t n)
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

static struct bml_vector *bml_vec_alloc_from_backing_copy(const char   *fn,
							  const double *back,
							  size_t	n)
{
	struct bml_vector *vec;

	vec = bml_vec_alloc_with_error(fn, n);
	if (!vec)
		return NULL;
	memcpy(vec->buf, back, n * sizeof(*back)); /* NOLINT */

	return vec;
}

struct bml_vector *bml_vector_alloc(size_t n)
{
	return bml_vec_alloc_with_error(__FUNCTION__, n);
}

struct bml_vector *bml_vector_alloc_copy(struct bml_vector *other)
{
	return bml_vec_alloc_from_backing_copy(__FUNCTION__, other->buf,
					       other->size);
}

struct bml_vector *bml_vector_from_array(double arr[], size_t n)
{
	return bml_vec_alloc_with_backing(__FUNCTION__, arr, n);
}

struct bml_vector *bml_vector_from_array_copy(double arr[], size_t n)
{
	return bml_vec_alloc_from_backing_copy(__FUNCTION__, arr, n);
}

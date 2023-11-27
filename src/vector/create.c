#include "alloc.h"
#include "block.h"
#include "vector.h"

struct bml_vector *bml_vec_alloc_with_error(const char *fn, size_t n)
{
	struct bml_vector *v;

	v = bml_alloc(fn, 1, sizeof(*v));
	if (!v)
		return NULL;

	v->b = bml_block_alloc(fn, n);
	if (!v->b)
	{
		free(v);
		return NULL;
	}

	return v;
}

struct bml_vector *bml_vector_alloc(size_t n)
{
	return bml_vec_alloc_with_error(__FUNCTION__, n);
}

struct bml_vector *bml_vector_alloc_copy(struct bml_vector *other)
{
	struct bml_vector *v;

	v = bml_alloc(__FUNCTION__, 1, sizeof(*v));
	if (!v)
		return NULL;

	v->b = bml_block_copy(__FUNCTION__, other->b);
	if (!v->b)
	{
		free(v);
		return NULL;
	}

	return v;
}

struct bml_vector *bml_vector_from_array(double arr[], size_t n)
{
	struct bml_vector *v;

	v = bml_alloc(__FUNCTION__, 1, sizeof(*v));
	if (!v)
		return NULL;

	v->b = bml_block_from_backing(__FUNCTION__, n, arr);
	if (!v->b)
	{
		free(v);
		return NULL;
	}

	return v;
}

struct bml_vector *bml_vector_from_array_copy(const double arr[], size_t n)
{
	struct bml_vector *v;

	v = bml_alloc(__FUNCTION__, 1, sizeof(*v));
	if (!v)
		return NULL;

	v->b = bml_block_alloc(__FUNCTION__, n);
	if (!v->b)
	{
		free(v);
		return NULL;
	}

	bml_block_copy_buf(v->b, arr);

	return v;
}

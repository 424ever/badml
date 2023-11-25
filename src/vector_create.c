#include "alloc.h"
#include "error.h"
#include "vector.h"

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

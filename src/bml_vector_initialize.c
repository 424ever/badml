#include <stdlib.h>

#include "bml_error_int.h"
#include "bml_vector.h"
#include "bml_vector_int.h"

void bml_vector_set_all(struct bml_vector *vec, double d)
{
	size_t i;

	for (i = 0; i < vec->size; ++i)
		vec->buf[i] = d;
}

void bml_vector_set_zero(struct bml_vector *vec)
{
	bml_vector_set_all(vec, 0.0);
}

void bml_vector_set_basis(struct bml_vector *vec, size_t i)
{
	bml_vector_set_zero(vec);
	vec->buf[i] = 1.0;
}

void bml_vector_copy(struct bml_vector *to, struct bml_vector *from)
{
	size_t i;

	if (to->size != from->size)
	{
		bml_error(__FUNCTION__, "different sizes");
		return;
	}

	for (i = 0; i < from->size; ++i)
		to->buf[i] = from->buf[i];
}

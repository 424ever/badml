#include <assert.h>
#include <stdlib.h>

#include "block.h"
#include "bml_vector.h"
#include "error.h"
#include "vector.h"

void bml_vector_set_all(struct bml_vector *vec, double d)
{
	size_t i;

	for (i = 0; i < bml_vector_size(vec); ++i)
		bml_block_must_set(vec->b, d, i);
}

void bml_vector_set_zero(struct bml_vector *vec)
{
	bml_vector_set_all(vec, 0.0);
}

void bml_vector_set_basis(struct bml_vector *vec, size_t i)
{
	bml_vector_set_zero(vec);
	bml_block_set(__FUNCTION__, vec->b, 1.0, i);
}

void bml_vector_copy(struct bml_vector *to, struct bml_vector *from)
{
	if (bml_vector_size(to) != bml_vector_size(from))
	{
		bml_error(__FUNCTION__, "different sizes");
		return;
	}

	bml_block_copy_buf(to->b, from->b->data);
}

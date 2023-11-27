#include "alloc.h"
#include "block.h"
#include "error.h"
#include "matrix.h"

struct bml_matrix *bml_matrix_alloc(struct bml_matrix_dim dim)
{
	struct bml_matrix *m;
	size_t		   count;

	if (!bml_matrix_dim_count(dim, &count))
	{
		bml_error(__FUNCTION__, "overflow in size calculation");
		return NULL;
	}

	m = bml_alloc(__FUNCTION__, 1, sizeof(*m));
	if (!m)
		return NULL;

	m->dim = dim;
	m->b   = bml_block_alloc(__FUNCTION__, count);
	if (!m->b)
	{
		free(m);
		return NULL;
	}

	return m;
}

int bml_matrix_dim_count(struct bml_matrix_dim dim, size_t *s)
{
	size_t tmp;

	tmp = dim.rows * dim.cols;

	if (dim.rows != 0 && *s / dim.rows != dim.cols)
		return 0;

	*s = tmp;

	return 1;
}

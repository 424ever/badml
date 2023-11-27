#include <math.h>

#include "block.h"
#include "bml_matrix.h"
#include "error.h"
#include "matrix.h"

static int bml_matrix_rangecheck(const char *fn, struct bml_matrix *m, size_t i,
				 size_t j)
{
	if (i >= m->dim.rows || j >= m->dim.cols)
	{
		bml_format_error(fn, "index (%zu, &zu) out of bounds");
		return 0;
	}

	return 1;
}

double bml_matrix_get(struct bml_matrix *m, size_t i, size_t j)
{
	double d;
	size_t idx;

	if (!bml_matrix_rangecheck(__FUNCTION__, m, i, j))
		return NAN;

	idx = bml_matrix_dim_idx_to_offset(m->dim, i, j);
	if (!bml_block_get(__FUNCTION__, m->b, &d, idx))
		return NAN;

	return d;
}

void bml_matrix_set(struct bml_matrix *m, size_t i, size_t j, double x)
{
	size_t idx;

	if (!bml_matrix_rangecheck(__FUNCTION__, m, i, j))
		return;

	idx = bml_matrix_dim_idx_to_offset(m->dim, i, j);
	bml_block_set(__FUNCTION__, m->b, x, idx);
}

double *bml_matrix_ptr(struct bml_matrix *m, size_t i, size_t j)
{
	size_t idx;

	if (!bml_matrix_rangecheck(__FUNCTION__, m, i, j))
		return NULL;

	idx = bml_matrix_dim_idx_to_offset(m->dim, i, j);

	return bml_block_ptr(__FUNCTION__, m->b, idx);
}

const double *bml_matrix_const_ptr(struct bml_matrix *m, size_t i, size_t j)
{
	size_t idx;

	if (!bml_matrix_rangecheck(__FUNCTION__, m, i, j))
		return NULL;

	idx = bml_matrix_dim_idx_to_offset(m->dim, i, j);

	return bml_block_ptr(__FUNCTION__, m->b, idx);
}

size_t bml_matrix_dim_idx_to_offset(struct bml_matrix_dim dim, size_t i,
				    size_t j)
{
	return i * dim.cols + j;
}

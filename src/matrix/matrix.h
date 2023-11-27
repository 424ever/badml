#ifndef BML_SRC_MATRIX_MATRIX_H_
#define BML_SRC_MATRIX_MATRIX_H_
#include "block.h"
#include "bml_matrix.h"

struct bml_matrix
{
	struct bml_matrix_dim dim;
	struct bml_block     *b;
};

int    bml_matrix_dim_count(struct bml_matrix_dim, size_t *);
size_t bml_matrix_dim_idx_to_offset(struct bml_matrix_dim, size_t i, size_t j);

#endif /* BML_SRC_MATRIX_MATRIX_H_ */

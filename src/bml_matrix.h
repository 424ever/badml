#ifndef BML_SRC_BML_MATRIX_H_
#define BML_SRC_BML_MATRIX_H_
#include <stddef.h>

struct bml_matrix;

struct bml_matrix_dim
{
	size_t rows;
	size_t cols;
};

/* creation */
struct bml_matrix *bml_matrix_alloc(struct bml_matrix_dim);

#endif /* BML_SRC_BML_MATRIX_H_ */

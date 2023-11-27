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

/* destruction */
void bml_matrix_free(struct bml_matrix *);

/* access */
double	      bml_matrix_get(struct bml_matrix *, size_t i, size_t j);
void	      bml_matrix_set(struct bml_matrix *, size_t i, size_t j, double);
double	     *bml_matrix_ptr(struct bml_matrix *, size_t i, size_t j);
const double *bml_matrix_const_ptr(struct bml_matrix *, size_t i, size_t j);

#endif /* BML_SRC_BML_MATRIX_H_ */

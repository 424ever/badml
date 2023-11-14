#ifndef BML_SRC_BML_VECTOR_INT_H_
#define BML_SRC_BML_VECTOR_INT_H_

#include <stdlib.h>

struct bml_vector
{
	size_t	size;
	double *buf;
	int	owning;
};

int  bml_vec_bounds_valid(struct bml_vector *vec, size_t i, const char *fn);
void bml_vec_copy_from_non_overlapping_buffer(struct bml_vector *vec,
					      const double *buf, size_t n);
struct bml_vector *bml_vec_alloc_with_error(const char *fn, size_t n);
struct bml_vector *bml_vec_alloc_with_backing(const char *fn, double *back,
					      size_t n);
struct bml_vector *bml_vec_alloc_from_backing_copy(const char	*fn,
						   const double *back,
						   size_t	 n);

#endif /* BML_SRC_BML_VECTOR_INT_H_ */

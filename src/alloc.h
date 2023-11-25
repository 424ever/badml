#ifndef BML_SRC_ALLOC_H_
#define BML_SRC_ALLOC_H_

#include <stdlib.h>

/* general */
void *bml_alloc(const char *fn, size_t nmemb, size_t size);

/* vector */
struct bml_vector *bml_vec_alloc_with_error(const char *fn, size_t n);
struct bml_vector *bml_vec_alloc_with_backing(const char *fn, double *back,
					      size_t n);
struct bml_vector *bml_vec_alloc_from_backing_copy(const char	*fn,
						   const double *back,
						   size_t	 n);
#endif /* BML_SRC_ALLOC_H_ */

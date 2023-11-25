#ifndef BML_SRC_VECTOR_VECTOR_H_
#define BML_SRC_VECTOR_VECTOR_H_
#include <stdlib.h>

#include "block.h"

struct bml_vector
{
	struct bml_block *b;
};

struct bml_vector *bml_vec_alloc_with_error(const char *fn, size_t n);

#endif /* BML_SRC_VECTOR_VECTOR_H_ */

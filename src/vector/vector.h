#ifndef BML_SRC_VECTOR_VECTOR_H_
#define BML_SRC_VECTOR_VECTOR_H_

#include <stdlib.h>

struct bml_vector
{
	size_t	size;
	double *buf;
	int	owning;
};

#endif /* BML_SRC_VECTOR_VECTOR_H_ */

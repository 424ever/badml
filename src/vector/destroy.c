#include <stdlib.h>

#include "block.h"
#include "vector.h"

void bml_vector_free(struct bml_vector *vec)
{
	bml_block_free(vec->b);
	free(vec);
}

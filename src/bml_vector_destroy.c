#include <stdlib.h>

#include "bml_vector_int.h"

void bml_vector_free(struct bml_vector *vec)
{
	if (!vec)
		return;

	if (vec->owning)
		free(vec->buf);
	free(vec);
}

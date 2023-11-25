#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "alloc.h"
#include "error.h"
#include "vector/vector.h"

void *bml_alloc(const char *fn, size_t nmemb, size_t size)
{
	void *p;

	if (nmemb == 0 || size == 0)
	{
		bml_error(fn, "attempted to allocate with size 0");
		return NULL;
	}

	p = calloc(nmemb, size);
	if (!p)
		bml_error(fn, "calloc failed");

	return p;
}

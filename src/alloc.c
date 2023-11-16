#include <errno.h>
#include <stdlib.h>

#include "alloc.h"
#include "error.h"

void *bml_alloc(const char *fn, size_t nmemb, size_t size)
{
	void *p;

	p = calloc(nmemb, size);
	if (!p)
		bml_error(fn, "calloc failed");

	return p;
}

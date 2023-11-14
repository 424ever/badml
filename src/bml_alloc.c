#include <errno.h>
#include <stdlib.h>

#include "bml_alloc.h"
#include "bml_error_int.h"

void *bml_alloc(const char *fn, size_t nmemb, size_t size)
{
	void *p;

	p = calloc(nmemb, size);
	if (!p)
		bml_error(fn, "calloc failed");

	return p;
}

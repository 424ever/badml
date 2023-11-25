#include <stdio.h>

#include "alloc.h"
#include "block.h"
#include "error.h"

#define REASON_BUFSIZ 128

struct bml_block *bml_block_alloc(const char *fn, size_t n)
{
	struct bml_block *b;

	b = bml_alloc(fn, 1, sizeof(*b));
	if (!b)
		return NULL;

	b->size	  = n;
	b->owning = 1;
	b->data	  = bml_alloc(fn, n, sizeof(*b->data));
	if (!b->data)
	{
		free(b);
		return NULL;
	}

	return b;
}

struct bml_block *bml_block_from_backing(const char *fn, size_t n, double *buf)
{
	struct bml_block *b;

	b = bml_alloc(fn, 1, sizeof(*b));
	if (!b)
		return NULL;

	b->size	  = n;
	b->owning = 0;
	b->data	  = buf;

	return b;
}

struct bml_block *bml_block_copy(const char *fn, const struct bml_block *b)
{
	struct bml_block *new;

	if (b->owning)
	{
		new = bml_block_alloc(fn, b->size);
		if (!new)
			return NULL;
		bml_block_copy_buf(new, b->data);
	}
	else
	{
		new = bml_block_from_backing(fn, b->size, b->data);
		if (!new)
			return NULL;
	}

	new->size   = b->size;
	new->owning = b->owning;

	return new;
}

void bml_block_copy_buf(struct bml_block *b, const double *buf)
{
	size_t i;

	for (i = 0; i < b->size; ++i)
	{
		b->data[i] = buf[i];
	}
}

void bml_block_free(struct bml_block *b)
{
	if (b->owning)
		free(b->data);
	free(b);
}

int bml_block_get(const char *fn, struct bml_block *b, double *d, size_t i)
{
	static char reason[REASON_BUFSIZ];

	if (i >= b->size)
	{
		(void) snprintf(reason, REASON_BUFSIZ,
				"index %zu out of bounds", i);
		bml_error(fn, reason);
		return 0;
	}

	*d = b->data[i];

	return 1;
}

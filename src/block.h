#ifndef BML_SRC_BLOCK_BLOCK_H_
#define BML_SRC_BLOCK_BLOCK_H_
#include <stddef.h>

struct bml_block
{
	size_t	size;
	double *data;
	int	owning;
};

struct bml_block *bml_block_alloc(const char *fn, size_t);
struct bml_block *bml_block_from_backing(const char *fn, size_t, double *);
struct bml_block *bml_block_copy(const char *fn, const struct bml_block *);
void		  bml_block_copy_buf(struct bml_block *, const double *);
void		  bml_block_free(struct bml_block *);
/* get an item in a block
 * on success, return 1 and store the value in *d
 * on failure, return 0 and call the error handler
 */
int bml_block_get(const char *fn, struct bml_block *, double *d, size_t i);

#endif /* BML_SRC_BLOCK_BLOCK_H_ */

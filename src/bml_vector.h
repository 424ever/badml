#ifndef BML_SRC_BML_VECTOR_H_
#define BML_SRC_BML_VECTOR_H_

#include <stdio.h>

struct bml_vector;

/* creation */
struct bml_vector *bml_vector_alloc(size_t n);
struct bml_vector *bml_vector_alloc_copy(const struct bml_vector *);
struct bml_vector *bml_vector_from_array(double[], size_t n);
struct bml_vector *bml_vector_from_array_copy(const double[], size_t n);

/* destruction */
void bml_vector_free(struct bml_vector *);

/* access */
size_t	      bml_vector_size(const struct bml_vector *);
void	      bml_vector_set(struct bml_vector *, size_t i, double);
double	      bml_vector_get(const struct bml_vector *, size_t i);
double	     *bml_vector_ptr(struct bml_vector *, size_t i);
const double *bml_vector_const_ptr(const struct bml_vector *, size_t i);
int bml_vector_eq(const struct bml_vector *, const struct bml_vector *);
int bml_vector_eq_tol(const struct bml_vector *, const struct bml_vector *,
		      double tol);

/* initialization */
void bml_vector_set_all(struct bml_vector *, double);
void bml_vector_set_zero(struct bml_vector *);
void bml_vector_set_basis(struct bml_vector *, size_t i);
void bml_vector_copy(struct bml_vector *to, struct bml_vector *from);

/* math */
double		   bml_vector_dot_product(const struct bml_vector *,
					  const struct bml_vector *);
struct bml_vector *bml_vector_cross_product(const struct bml_vector *,
					    const struct bml_vector *);

/* io */
int bml_vector_print(FILE *, const struct bml_vector *, const char *format);

#endif /* BML_SRC_BML_VECTOR_H_ */

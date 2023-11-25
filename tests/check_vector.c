#include <check.h>
#include <dlfcn.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bml_error.h"
#include "bml_vector.h"

static const double	  test_val_1	= 42.0;
static const double	  test_val_2	= 21.0;
static const size_t	  test_vec_size = 5;
static int		  errcount	= 0;
static struct bml_vector *vec;

static void handler(const char *f, const char *r)
{
	(void) fprintf(stderr, "function %s reason %s error %s\n", f, r,
		       strerror(errno));
	++errcount;
}

static void setup(void)
{
	bml_set_err_handler(&handler);
	vec = bml_vector_alloc(test_vec_size);
	ck_assert_ptr_nonnull(vec);
	ck_assert_int_eq(errcount, 0);
}

static void teardown(void)
{
	bml_vector_free(vec);
}

static void fill_vec()
{
	/* NOLINTBEGIN */
	bml_vector_set(vec, 0, 1.0);
	bml_vector_set(vec, 1, 2.0);
	bml_vector_set(vec, 2, 3.0);
	bml_vector_set(vec, 3, 4.0);
	bml_vector_set(vec, 4, 5.0);
	/* NOLINTEND */
}

START_TEST(test_alloc_fail)
{
	ck_assert_ptr_null(bml_vector_alloc(ULONG_MAX));
	ck_assert_ptr_null(bml_vector_alloc(0));
	ck_assert_int_eq(errcount, 2);
}
END_TEST

START_TEST(test_size)
{
	ck_assert_int_eq(bml_vector_size(vec), test_vec_size);
}
END_TEST

START_TEST(test_get)
{
	ck_assert_double_eq(bml_vector_get(vec, 0), 0.0);
}
END_TEST

START_TEST(test_get_oob)
{
	ck_assert_double_nan(bml_vector_get(vec, test_vec_size));
	ck_assert_int_eq(errcount, 1);
}
END_TEST

START_TEST(test_init_vals)
{
	size_t i;

	for (i = 0; i < test_vec_size; ++i)
		ck_assert_double_eq(bml_vector_get(vec, i), 0.0);
}
END_TEST

START_TEST(test_set)
{
	size_t i;

	for (i = 0; i < test_vec_size; ++i)
	{
		ck_assert_double_ne(bml_vector_get(vec, i), test_val_1);
		bml_vector_set(vec, i, test_val_1);
		ck_assert_double_eq(bml_vector_get(vec, i), test_val_1);
	}
}
END_TEST

START_TEST(test_set_oob)
{
	bml_vector_set(vec, test_vec_size, test_val_1);
	ck_assert_int_eq(errcount, 1);
}
END_TEST

START_TEST(test_const_ptr)
{
	const double *p;

	p = bml_vector_const_ptr(vec, 0);
	bml_vector_set(vec, 0, test_val_1);
	ck_assert_double_eq(*p, test_val_1);
}
END_TEST

START_TEST(test_const_ptr_oob)
{
	ck_assert_ptr_null(bml_vector_const_ptr(vec, test_vec_size));
	ck_assert_int_eq(errcount, 1);
}
END_TEST

START_TEST(test_ptr)
{
	double *p;

	p = bml_vector_ptr(vec, 0);
	bml_vector_set(vec, 0, test_val_1);
	ck_assert_double_eq(*p, test_val_1);
	*p = test_val_2;
	ck_assert_double_eq(bml_vector_get(vec, 0), test_val_2);
}
END_TEST

START_TEST(test_ptr_oob)
{
	ck_assert_ptr_null(bml_vector_ptr(vec, test_vec_size));
	ck_assert_int_eq(errcount, 1);
}
END_TEST

START_TEST(test_set_all)
{
	size_t i;

	bml_vector_set_all(vec, test_val_1);
	for (i = 0; i < test_vec_size; ++i)
		ck_assert_double_eq(bml_vector_get(vec, i), test_val_1);
}
END_TEST

START_TEST(test_set_zero)
{
	size_t i;

	bml_vector_set_zero(vec);
	for (i = 0; i < test_vec_size; ++i)
		ck_assert_double_eq(bml_vector_get(vec, i), 0.0);
}
END_TEST

START_TEST(test_set_basis)
{
	double check_val;
	size_t i;

	bml_vector_set_basis(vec, 2);
	for (i = 0; i < test_vec_size; ++i)
	{
		check_val = i == 2 ? 1.0 : 0.0;
		ck_assert_double_eq(bml_vector_get(vec, i), check_val);
	}
}
END_TEST

START_TEST(test_print)
{
	const char exp[] = "a1.0\na2.0\na3.0\na4.0\na5.0\n";
	char	  *buf;
	size_t	   buflen;
	FILE	  *f;
	int	   ret;

	fill_vec();
	buf    = NULL;
	buflen = 0;
	f      = open_memstream(&buf, &buflen);
	ret    = bml_vector_print(f, vec, "a%.1f");
	ck_assert_int_eq(ret, strlen(exp));
	ck_assert_int_eq(fflush(f), 0);
	ck_assert_str_eq(buf, exp);
	ck_assert_int_eq(fclose(f), 0);
	free(buf);
}
END_TEST

START_TEST(test_print_fail)
{
	char  buf[32]; /* NOLINT */
	FILE *f;
	int   ret;

	fill_vec();
	f = fmemopen(buf, 32, "r"); /* NOLINT */
	mark_point();
	ret = bml_vector_print(f, vec, "a%.1f");
	ck_assert_int_eq(ret, -1);
	ck_assert_int_eq(errcount, 1);
	(void) fclose(f);
}
END_TEST

START_TEST(test_alloc_copy)
{
	size_t		   i;
	struct bml_vector *copy;

	fill_vec();
	copy = bml_vector_alloc_copy(vec);
	ck_assert_int_eq(bml_vector_size(vec), bml_vector_size(copy));
	for (i = 0; i < test_vec_size; ++i)
		ck_assert_double_eq(bml_vector_get(copy, i),
				    bml_vector_get(vec, i));
	bml_vector_set_zero(vec);
	for (i = 0; i < test_vec_size; ++i)
	{
		ck_assert_double_ne(bml_vector_get(copy, i), 0.0);
		ck_assert_double_eq(bml_vector_get(vec, i), 0.0);
	}
	bml_vector_free(copy);
}
END_TEST

START_TEST(test_from_array)
{
	double		   arr[] = {1.0, 2.0, 3.0, 4.0}; /* NOLINT */
	size_t		   i;
	struct bml_vector *vec;
	struct bml_vector *copy;

	vec  = bml_vector_from_array(arr, 4);
	copy = bml_vector_alloc_copy(vec);
	ck_assert_ptr_eq(bml_vector_ptr(vec, 0), arr);
	for (i = 0; i < 4; ++i)
		ck_assert_double_eq(bml_vector_get(vec, i), arr[i]);
	arr[0] = test_val_1;
	ck_assert_double_eq(bml_vector_get(vec, 0), test_val_1);
	ck_assert_double_eq(bml_vector_get(copy, 0), test_val_1);
	bml_vector_set(vec, 1, test_val_2);
	ck_assert_double_eq(arr[1], test_val_2);
	ck_assert_double_eq(bml_vector_get(copy, 1), test_val_2);
	bml_vector_set(copy, 0, test_val_1 + test_val_2);
	ck_assert_double_eq(arr[0], test_val_1 + test_val_2);
	ck_assert_double_eq(bml_vector_get(vec, 0), test_val_1 + test_val_2);
	bml_vector_free(vec);
	bml_vector_free(copy);
}
END_TEST

START_TEST(test_from_array_copy)
{
	double		   arr[] = {1.0, 2.0, 3.0, 4.0}; /* NOLINT */
	size_t		   i;
	struct bml_vector *vec;

	vec = bml_vector_from_array_copy(arr, 4);
	ck_assert_ptr_ne(bml_vector_ptr(vec, 0), arr);
	for (i = 0; i < 4; ++i)
		ck_assert_double_eq(bml_vector_get(vec, i), arr[i]);
	arr[0] = test_val_1;
	ck_assert_double_eq(bml_vector_get(vec, 0), 1.0);
	bml_vector_set(vec, 1, test_val_2);
	ck_assert_double_eq(arr[1], 2.0); /* NOLINT */
	bml_vector_free(vec);
}
END_TEST

START_TEST(test_copy)
{
	size_t		   i;
	struct bml_vector *copy;

	fill_vec();
	copy = bml_vector_alloc(test_vec_size);
	bml_vector_copy(copy, vec);
	for (i = 0; i < test_vec_size; ++i)
		ck_assert_double_eq(bml_vector_get(copy, i),
				    bml_vector_get(vec, i));
	bml_vector_set_zero(vec);
	for (i = 0; i < test_vec_size; ++i)
	{
		ck_assert_double_ne(bml_vector_get(copy, i), 0.0);
		ck_assert_double_eq(bml_vector_get(vec, i), 0.0);
	}
	bml_vector_free(copy);
}
END_TEST

START_TEST(test_copy_fail)
{
	struct bml_vector *copy;

	copy = bml_vector_alloc(test_vec_size + 1);
	bml_vector_copy(copy, vec);
	ck_assert_int_eq(errcount, 1);
	bml_vector_free(copy);
}
END_TEST

START_TEST(test_dot_product)
{
	double		   arr1[] = {1.0, 3.0, 5.0}; /* NOLINT */
	double		   arr2[] = {2.0, 4.0, 6.0}; /* NOLINT */
	struct bml_vector *vec1;
	struct bml_vector *vec2;

	vec1 = bml_vector_from_array(arr1, 3);
	vec2 = bml_vector_from_array(arr2, 3);

	ck_assert_double_eq(bml_vector_dot_product(vec1, vec2),
			    44.0); /* NOLINT */
	ck_assert_int_eq(errcount, 0);

	bml_vector_free(vec1);
	bml_vector_free(vec2);
}
END_TEST

START_TEST(test_dot_product_fail)
{
	double		   arr1[] = {1.0, 3.0, 5.0};	  /* NOLINT */
	double		   arr2[] = {2.0, 4.0, 6.0, 8.0}; /* NOLINT */
	struct bml_vector *vec1;
	struct bml_vector *vec2;

	vec1 = bml_vector_from_array(arr1, 3);
	vec2 = bml_vector_from_array(arr2, 4);

	ck_assert_double_nan(bml_vector_dot_product(vec1, vec2));
	ck_assert_int_eq(errcount, 1);

	bml_vector_free(vec1);
	bml_vector_free(vec2);
}
END_TEST

START_TEST(test_eq)
{
	double		   arr1[3] = {1.0, 2.0, 3.0};	   /* NOLINT */
	double		   arr2[3] = {1.0, 2.0, 3.0};	   /* NOLINT */
	double		   arr3[4] = {1.0, 2.0, 3.0, 4.0}; /* NOLINT */
	struct bml_vector *vec1;
	struct bml_vector *vec2;
	struct bml_vector *vec3;

	vec1 = bml_vector_from_array(arr1, 3);
	vec2 = bml_vector_from_array(arr2, 3);
	vec3 = bml_vector_from_array(arr3, 4);

	ck_assert(bml_vector_eq(vec1, vec2));
	ck_assert(!bml_vector_eq(vec1, vec3));
	bml_vector_set(vec1, 0, 1.00001); /* NOLINT */
	ck_assert(!bml_vector_eq(vec1, vec2));

	bml_vector_free(vec1);
	bml_vector_free(vec2);
	bml_vector_free(vec3);

	ck_assert_int_eq(errcount, 0);
}
END_TEST

START_TEST(test_eq_tol)
{
	double		   arr1[3] = {1.0, 2.0, 3.0};	   /* NOLINT */
	double		   arr2[3] = {1.1, 1.8, 3.0};	   /* NOLINT */
	double		   arr3[4] = {1.0, 2.0, 3.0, 4.0}; /* NOLINT */
	struct bml_vector *vec1;
	struct bml_vector *vec2;
	struct bml_vector *vec3;

	vec1 = bml_vector_from_array(arr1, 3);
	vec2 = bml_vector_from_array(arr2, 3);
	vec3 = bml_vector_from_array(arr3, 4);

	ck_assert(!bml_vector_eq_tol(vec1, vec3, 10.0)); /* NOLINT */
	ck_assert(bml_vector_eq_tol(vec1, vec2, 0.3));	 /* NOLINT */
	ck_assert(!bml_vector_eq_tol(vec1, vec2, 0.1));	 /* NOLINT */

	bml_vector_free(vec1);
	bml_vector_free(vec2);
	bml_vector_free(vec3);

	ck_assert_int_eq(errcount, 0);
}
END_TEST

START_TEST(test_cross_product)
{
	double		   arr1[] = {2.0, 3.0, 4.0};   /* NOLINT */
	double		   arr2[] = {5.0, 6.0, 7.0};   /* NOLINT */
	double		   exp[]  = {-3.0, 6.0, -3.0}; /* NOLINT */
	struct bml_vector *vec1;
	struct bml_vector *vec2;
	struct bml_vector *expv;
	struct bml_vector *res;

	vec1 = bml_vector_from_array(arr1, 3);
	vec2 = bml_vector_from_array(arr2, 3);
	expv = bml_vector_from_array(exp, 3);

	res = bml_vector_cross_product(vec1, vec2);

	ck_assert(bml_vector_eq(expv, res));
	ck_assert_int_eq(errcount, 0);

	bml_vector_free(vec1);
	bml_vector_free(vec2);
	bml_vector_free(expv);
	bml_vector_free(res);
}
END_TEST

START_TEST(test_cross_product_fail)
{
	double		   arr1[] = {1.0, 3.0, 5.0};	  /* NOLINT */
	double		   arr2[] = {2.0, 4.0, 6.0, 8.0}; /* NOLINT */
	struct bml_vector *vec1;
	struct bml_vector *vec2;

	vec1 = bml_vector_from_array(arr1, 3);
	vec2 = bml_vector_from_array(arr2, 4);

	ck_assert_ptr_null(bml_vector_cross_product(vec1, vec2));
	ck_assert_ptr_null(bml_vector_cross_product(vec2, vec1));
	ck_assert_ptr_null(bml_vector_cross_product(vec2, vec2));
	ck_assert_int_eq(errcount, 3);

	bml_vector_free(vec1);
	bml_vector_free(vec2);
}
END_TEST

Suite *vector_suite(void)
{
	Suite *s;
	TCase *tc_access;
	TCase *tc_create;
	TCase *tc_init;
	TCase *tc_io;
	TCase *tc_math;

	s = suite_create("vector");

	tc_create = tcase_create("create");
	tc_access = tcase_create("access");
	tc_init	  = tcase_create("init");
	tc_io	  = tcase_create("io");
	tc_math	  = tcase_create("math");

	tcase_add_checked_fixture(tc_access, &setup, &teardown);
	tcase_add_checked_fixture(tc_create, &setup, &teardown);
	tcase_add_checked_fixture(tc_init, &setup, &teardown);
	tcase_add_checked_fixture(tc_io, &setup, &teardown);
	tcase_add_checked_fixture(tc_math, &setup, &teardown);

	suite_add_tcase(s, tc_access);
	suite_add_tcase(s, tc_create);
	suite_add_tcase(s, tc_init);
	suite_add_tcase(s, tc_io);
	suite_add_tcase(s, tc_math);

	tcase_add_test(tc_access, test_const_ptr);
	tcase_add_test(tc_access, test_const_ptr_oob);
	tcase_add_test(tc_access, test_eq);
	tcase_add_test(tc_access, test_eq_tol);
	tcase_add_test(tc_access, test_get);
	tcase_add_test(tc_access, test_get_oob);
	tcase_add_test(tc_access, test_ptr);
	tcase_add_test(tc_access, test_ptr_oob);
	tcase_add_test(tc_access, test_set);
	tcase_add_test(tc_access, test_set_oob);
	tcase_add_test(tc_access, test_size);
	tcase_add_test(tc_create, test_alloc_copy);
	tcase_add_test(tc_create, test_alloc_fail);
	tcase_add_test(tc_create, test_from_array);
	tcase_add_test(tc_create, test_from_array_copy);
	tcase_add_test(tc_create, test_init_vals);
	tcase_add_test(tc_init, test_copy);
	tcase_add_test(tc_init, test_copy_fail);
	tcase_add_test(tc_init, test_set_all);
	tcase_add_test(tc_init, test_set_basis);
	tcase_add_test(tc_init, test_set_zero);
	tcase_add_test(tc_io, test_print);
	tcase_add_test(tc_io, test_print_fail);
	tcase_add_test(tc_math, test_cross_product);
	tcase_add_test(tc_math, test_cross_product_fail);
	tcase_add_test(tc_math, test_dot_product);
	tcase_add_test(tc_math, test_dot_product_fail);

	return s;
}

int main(void)
{
	int	 failed;
	Suite	*s;
	SRunner *sr;

	s  = vector_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

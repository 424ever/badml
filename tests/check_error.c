#include <check.h>
#include <signal.h>
#include <stdlib.h>

#include "bml_error.h"
#include "bml_error_int.h"

#define TEST_REASON "test-reason"

static const char *test_function;
static const char *test_reason;

static void test_handler(const char *function, const char *reason)
{
	test_function = function;
	test_reason   = reason;
}

START_TEST(test_default_handler)
{
	ck_assert_ptr_eq(&bml_error_default_handler, bml_get_err_handler());
	bml_error("test_default_handler", TEST_REASON);
}
END_TEST

START_TEST(test_set_handler)
{
	bml_err_handler_t *old_handler;

	old_handler = bml_set_err_handler(&test_handler);
	bml_error("test_set_handler", TEST_REASON);

	ck_assert_ptr_eq(old_handler, &bml_error_default_handler);
	ck_assert_ptr_eq(&test_handler, bml_get_err_handler());
	ck_assert_str_eq(test_function, "test_set_handler");
	ck_assert_str_eq(test_reason, TEST_REASON);
}
END_TEST

START_TEST(test_null_handler)
{
	bml_err_handler_t *old_handler;

	old_handler = bml_set_err_handler_off();
	bml_error("test_null_handler", TEST_REASON);

	ck_assert_ptr_eq(old_handler, &bml_error_default_handler);
	ck_assert_ptr_eq(&bml_error_null_handler, bml_get_err_handler());
	ck_assert_ptr_null(test_function);
	ck_assert_ptr_null(test_reason);
}
END_TEST

Suite *error_suite(void)
{
	Suite *s;
	TCase *tc_core;

	s = suite_create("error");

	tc_core = tcase_create("core");

	tcase_add_test_raise_signal(tc_core, test_default_handler, SIGABRT);
	tcase_add_test(tc_core, test_set_handler);
	tcase_add_test(tc_core, test_null_handler);
	suite_add_tcase(s, tc_core);

	return s;
}

int main(void)
{
	int	 failed;
	Suite	*s;
	SRunner *sr;

	s  = error_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}

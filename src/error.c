#include <stdio.h>
#include <stdlib.h>

#include "bml_error.h"
#include "error.h"

static bml_err_handler_t *current_handler = &bml_error_default_handler;

bml_err_handler_t *bml_set_err_handler(bml_err_handler_t *new_handler)
{
	bml_err_handler_t *old_handler;

	old_handler	= current_handler;
	current_handler = new_handler;

	return old_handler;
}

bml_err_handler_t *bml_set_err_handler_off(void)
{
	bml_err_handler_t *old_handler;

	old_handler	= current_handler;
	current_handler = &bml_error_null_handler;

	return old_handler;
}

bml_err_handler_t *bml_get_err_handler(void)
{
	return current_handler;
}

void bml_error_default_handler(const char *function, const char *reason)
{
	(void) fprintf(stderr, "Error while calling %s: %s\n", function,
		       reason);
	abort();
}

void bml_error_null_handler(const char *function, const char *reason)
{
	(void) function;
	(void) reason;
}

void bml_error(const char *function, const char *reason)
{
	current_handler(function, reason);
}

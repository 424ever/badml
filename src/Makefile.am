AM_CFLAGS = @AM_CFLAGS@

lib_LTLIBRARIES = libbadml.la

libbadml_la_SOURCES = bml_alloc.c             \
		      bml_alloc.h             \
		      bml_error.c             \
		      bml_error.h             \
		      bml_error_int.h         \
		      bml_vector_access.c     \
		      bml_vector_create.c     \
		      bml_vector_destroy.c    \
		      bml_vector_initialize.c \
		      bml_vector_io.c         \
		      bml_vector_math.c       \
		      bml_vector_util.c       \
		      bml_vector.h            \
		      bml_vector_int.h

include_HEADERS = bml_error.h  \
		  bml_vector.h

lint: $(libbadml_la_SOURCES)
	$(CLANG_TIDY) $^

check-local: lint

.PHONY: lint

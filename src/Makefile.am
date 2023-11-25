AM_CFLAGS = @AM_CFLAGS@

lib_LTLIBRARIES = libbadml.la

libbadml_la_SOURCES = alloc.c          \
		      alloc.h          \
		      bml_error.h      \
		      bml_vector.h     \
		      error.c          \
		      error.h          \
		      vector.h         \
		      vector_access.c  \
		      vector_create.c  \
		      vector_destroy.c \
		      vector_init.c    \
		      vector_io.c      \
		      vector_math.c 

include_HEADERS = bml_error.h  \
		  bml_vector.h

lint: $(libbadml_la_SOURCES)
	$(CLANG_TIDY) $^

check-local: lint

.PHONY: lint

AM_CFLAGS = @AM_CFLAGS@

lib_LTLIBRARIES = libbadml.la

libbadml_la_SOURCES = alloc.c          \
		      alloc.h          \
		      block.c          \
		      block.h          \
		      bml_error.h      \
		      bml_matrix.h     \
		      bml_vector.h     \
		      error.c          \
		      error.h          \
		      matrix/matrix.h  \
		      matrix/access.c  \
		      matrix/create.c  \
		      vector/vector.h  \
		      vector/access.c  \
		      vector/create.c  \
		      vector/destroy.c \
		      vector/init.c    \
		      vector/io.c      \
		      vector/math.c 

include_HEADERS = bml_error.h  \
		  bml_matrix.h \
		  bml_vector.h

lint: $(libbadml_la_SOURCES)
	$(CLANG_TIDY) $^

check-local: lint

.PHONY: lint

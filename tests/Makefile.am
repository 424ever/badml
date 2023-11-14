TESTS = check_error \
	check_vector

check_PROGRAMS = check_error \
		 check_vector

check_error_SOURCES = check_error.c                   \
		      $(top_builddir)/src/bml_error.h \
		      $(top_builddir)/src/bml_error_internal.h
check_error_CFLAGS = @CHECK_CFLAGS@
check_error_LDADD = $(top_builddir)/src/libbadml.la @CHECK_LIBS@

check_vector_SOURCES = check_vector.c \
		       $(top_builddir)/src/bml_vector.h
check_vector_CFLAGS = @CHECK_CFLAGS@
check_vector_LDADD = $(top_builddir)/src/libbadml.la @CHECK_LIBS@

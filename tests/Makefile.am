include $(top_srcdir)/aminclude_static.am

AM_CFLAGS = @AM_CFLAGS@

@VALGRIND_CHECK_RULES@

TESTS = check_error \
	check_vector

check_PROGRAMS = check_error \
		 check_vector

check_error_SOURCES = check_error.c                 \
		      $(top_srcdir)/src/error.c     \
		      $(top_srcdir)/src/bml_error.h \
		      $(top_srcdir)/src/error.h
check_error_CFLAGS = @CHECK_CFLAGS@ $(AM_CFLAGS) $(CODE_COVERAGE_CFLAGS) -I$(top_srcdir)/src
check_error_CPPFLAGS = $(CODE_COVERAGE_CPPFLAGS)
check_error_LDFLAGS = $(CODE_COVERAGE_LDFLAGS)
check_error_LDADD = @CHECK_LIBS@ $(CODE_COVERAGE_LIBS)

check_vector_SOURCES = check_vector.c                     \
		       $(top_srcdir)/src/alloc.c          \
		       $(top_srcdir)/src/error.c          \
		       $(top_srcdir)/src/vector_access.c  \
		       $(top_srcdir)/src/vector_create.c  \
		       $(top_srcdir)/src/vector_destroy.c \
		       $(top_srcdir)/src/vector_init.c    \
		       $(top_srcdir)/src/vector_io.c      \
		       $(top_srcdir)/src/vector_math.c    \
		       $(top_srcdir)/src/vector_util.c    \
		       $(top_srcdir)/src/bml_vector.h

check_vector_CFLAGS = @CHECK_CFLAGS@ $(AM_CFLAGS) $(CODE_COVERAGE_CFLAGS) -I$(top_srcdir)/src
check_vector_CPPFLAGS = $(CODE_COVERAGE_CPPFLAGS)
check_vector_LDFLAGS = $(CODE_COVERAGE_LDFLAGS)
check_vector_LDADD = @CHECK_LIBS@ $(CODE_COVERAGE_LIBS)

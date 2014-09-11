# Process this file with autoconf to create a configure script
# (c) 2014 Daniel Stein

AC_INIT([pusher], [0.2], [d.stein@hackherz.com])



# tests
## compiler
AC_PROG_CXX
AC_LANG(C++)

GXX_VERSION="`$CXX -dumpversion`"


## check for headers
AC_CHECK_HEADERS(iostream string sstream fstream vector)


## check for libraries
AC_LANG_PUSH([C++])
	AC_CHECK_HEADERS([boost/foreach.hpp], [], [AC_MSG_ERROR(You need the Boost libraries.)])
	AC_CHECK_HEADERS([boost/format.hpp], [], [AC_MSG_ERROR(You need the Boost libraries.)])
	AC_CHECK_HEADERS([boost/property_tree/ptree.hpp], [], [AC_MSG_ERROR(You need the Boost libraries.)])
	AC_CHECK_HEADERS([boost/property_tree/ini_parser.hpp], [], [AC_MSG_ERROR(You need the Boost libraries.)])
	AC_CHECK_HEADERS([boost/program_options.hpp], [], [AC_MSG_ERROR(You need the Boost Program Options library.)])
	AC_CHECK_HEADERS([boost/regex.hpp], [], [AC_MSG_ERROR(You need the Boost Regex library.)])
	AC_CHECK_HEADERS([curl/curl.h], [], [AC_MSG_ERROR(You need the curl libraries.)])
AC_LANG_POP([C++])


# write makefile
AC_OUTPUT(makefile)


# output
cat <<EOF

Configured for building ${PACKAGE_NAME} ${PACKAGE_VERSION}

Compiler .................................... ${CXX}
Compiler version ............................ ${GXX_VERSION}

Configure finished. Do 'make' to compile.
EOF


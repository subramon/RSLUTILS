#!/bin/bash
set -e 


INCS="-I${RSLUTILS_SRC_ROOT}/inc/ -I${RSUTILS_SRC_ROOT}/inc/"
LIBS="${RSLUTILS_SRC_ROOT}/src/librslutils.so ${RSUTILS_SRC_ROOT}/src/librsutils.so"

# LUAJIT_SO := /usr/lib/x86_64-linux-gnu/libluajit-5.1.so.2
# LUAJIT_SO := /usr/local/lib/libluajit-5.1.so
LUAJIT_SO=/home/subramon/luajit/src/libluajit.so

rm -f ./a.out
gcc test_get_strings.c \
  ${INCS} ${LIBS} ${LUAJIT_SO}
./a.out

rm -f ./a.out
gcc test_get_nums.c \
  ${INCS} ${LIBS} ${LUAJIT_SO}
./a.out

rm -f ./a.out

echo "Completed $0 onin $PWD"

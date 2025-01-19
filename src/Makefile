#!/bin/bash

CFLAGS := -g -O0 # optimizations cause buffer overflow on maas
# CFLAGS := -O3

CFLAGS += -DDEBUG
CFLAGS += -fopenmp
CFLAGS += -fstrict-aliasing 
CFLAGS += -std=gnu99 -Wall -fPIC -W -Waggregate-return -Wcast-align 
CFLAGS += -Wstrict-aliasing
# CFLAGS += -Wincompatible-pointer-types # comment for CentOS
CFLAGS += -Wmissing-prototypes -Wnested-externs -Wshadow -Wwrite-strings 
CFLAGS += -Wunused-variable -Wunused-parameter 
CFLAGS += -Wstrict-prototypes -Wmissing-prototypes -Wpointer-arith 
CFLAGS += -Wmissing-declarations -Wredundant-decls -Wnested-externs 
CFLAGS += -Wshadow -Wcast-qual -Wcast-align -Wwrite-strings 
CFLAGS += -Wold-style-definition 
CFLAGS += -Wattributes
CFLAGS += -Wunused-label 
# CFLAGS += -Wint-conversion # comment for CentOS
CFLAGS += -Wconversion
# CFLAGS += -Wnull-dereference  # comment for CentOS
CFLAGS += -Wpedantic 
CFLAGS += -Wuninitialized
#---------------
CC = gcc 
INCS :=-I../inc/ 
INCS +=-I${RSUTILS_SRC_ROOT}/inc/

MYSO = librslutils.so

all : ${MYSO}  

# LUAJIT_SO := /usr/lib/x86_64-linux-gnu/libluajit-5.1.so.2
LUAJIT_SO := /usr/local/lib/libluajit-5.1.so

#--------
.c.o :
	$(CC) -c -o $@ $< $(QCFLAGS)  $(INCS)

SRCS := bridge_read_configs.c 
SRCS += load_configs.c
SRCS += mk_lua_state.c
SRCS += check_args_is_table.c
SRCS += get_array_of_nums.c
SRCS += get_array_of_strings.c
SRCS += get_bool_from_tbl.c
SRCS += get_num_from_tbl.c
SRCS += get_str_from_tbl.c
SRCS += put_tbl.c

OBJS = $(SRCS:.c=.o)
#----------------------------------
${MYSO} : ${OBJS}  
	gcc -shared -fPIC ${QCFLAGS} ${OBJS} -o ${MYSO} 

clean :
	rm -f _*
	rm -f *.so
	rm -f *.o
	rm -f  ${MYSO}

EXTRA_FLAGS=-O2 -Wall -static -pipe

CC=gcc
CFLAGS=-x c -std=c11 ${EXTRA_FLAGS}
CXX=g++
CXXFLAGS=-x c++ -std=c++11 ${EXTRA_FLAGS}

TARGET=solution
SOURCES=$(wildcard *.c)
ifeq ($(SOURCES),)
  SOURCES=$(wildcard *.cc)
  COMPILER=${CXX} ${CXXFLAGS}
else
  COMPILER=${CC} ${CFLAGS}
endif

.PHONY: all run

all: ${TARGET}

sample_*.in: ${TARGET} FORCE
	@f=$$(basename $@ .in); \
	echo "cat $@ | ./${TARGET}"; \
	cat $@ | \
	    /usr/bin/time --format="%M/%X/%K/%p/%t KB | %P CPU | %e/%S/%U seconds" \
	    ./${TARGET} | diff --color=always -sZ $$f.ans -

test_*.in: ${TARGET} FORCE
	@echo "cat $@ | ./${TARGET}"; \
	cat $@ | \
	    /usr/bin/time --format="%M/%X/%K/%p/%t KB | %P CPU | %e/%S/%U seconds" \
	    ./${TARGET}

FORCE:

run: ${TARGET}
	@for a in *.in; \
	do \
	  echo "Testing: $$a"; \
	  f=$$(basename $$a .in); \
	  cat $$a | \
	      ./${TARGET} | \
		  diff --color=always -Z $$f.ans -; \
	  true; \
	done

${TARGET}: ${SOURCES}
	${COMPILER} -o $@ $<

DEBUG := 1
TITLE := tmpswap
OUT := ${TITLE}
MAIN_OBJ := src/${OUT}.o
LIB_OBJ := $(filter-out ${MAIN_OBJ},$(patsubst %.cc,%.o,$(wildcard src/*.cc)))
DEP := ${LIB_OBJ:.o=.dep} ${MAIN_OBJ:.o=.dep}
VERSION := $(shell git describe --dirty 2>/dev/null || echo v0)
CXX_STD := 14
LDLIBS := -lboost_filesystem -lboost_system
ifeq (${DEBUG},1)
  CXXFLAGS := -std=c++${CXX_STD} -Wall -g -O0
else
  CXXFLAGS := -std=c++${CXX_STD} -O2
endif
ARFLAGS := r

.PHONY: all clean distclean clean-out distclean-out

all: src/${OUT}

clean: clean-out

distclean: distclean-out

ifneq "${MAKECMDGOALS}" "clean"
ifneq "${MAKECMDGOALS}" "distclean"
  -include ${DEP}
endif
endif

%.dep: %.cc src/static_config.hh
	${COMPILE.cc} -MG -MM -MP -MT$@ -MT${<:.cc=.o} $< >$@

clean-out:
	rm -f src/static_config.hh src/lib${OUT}.a ${MAIN_OBJ} ${LIB_OBJ} ${DEP}

distclean-out: clean-out
	rm -rf ${OUT}

src/static_config.hh: src/static_config.hh.in
	perl -pe "s/{PACKAGE_TITLE}/${TITLE}/; s/{PACKAGE_NAME}/${OUT}/; s/{PACKAGE_VERSION}/${VERSION}/; s/{PACKAGE_STRING}/${TITLE} ${VERSION}/;" <$^ >$@

src/lib${OUT}.a: ${LIB_OBJ}
	${AR} ${ARFLAGS} $@ $^

ifeq (${DEBUG},1)
src/${OUT}: src/lib${OUT}.a ${MAIN_OBJ}
	${LINK.cc} ${LDLIBS} ${OUTPUT_OPTION} $^
else
src/${OUT}: src/lib${OUT}.a ${MAIN_OBJ}
	${LINK.cc} ${LDLIBS} ${OUTPUT_OPTION} $^
	strip $@
endif

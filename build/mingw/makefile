projectname     = pyrope
configuration   = debug

intdir      = ./objs
outdir      = ../../lib

srcdir      = ../../src


src0        = $(srcdir)/handle.c
src1        = $(srcdir)/win32io.c
src2        = $(srcdir)/win32ioutil.c

obj0        = $(intdir)/handle.o
obj1        = $(intdir)/win32io.o
obj2        = $(intdir)/win32ioutil.o

objs        = $(obj0) $(obj1) $(obj2)

target_ext  = a
target      = $(outdir)/lib$(projectname).$(target_ext)


# 
# コマンドカテゴリ
# 
cc      = gcc
cflags  = -O2 -Wall -Wextra -Wformat=2 -Wcast-qual -Wcast-align \
          -Wfloat-equal -Wpointer-arith -fsigned-char \
          -I"../../include" -I "../../../libgarnet/include" -D_DEBUG

rm      = rm
rmflags = -v


ar      = ar
arflags = -srcv


# 
# レシピ
# 
.PHONY: all
all: $(target)

$(target): $(objs)
	$(ar) $(arflags) $@ $(objs)

$(obj0): $(src0)
	@if [ ! -d $(intdir) ]; then mkdir -vp $(intdir); fi
	$(cc) $(cflags) -c $< -o $@

$(obj1): $(src1)
	@if [ ! -d $(intdir) ]; then mkdir -vp $(intdir); fi
	$(cc) $(cflags) -c $< -o $@

$(obj2): $(src2)
	@if [ ! -d $(intdir) ]; then mkdir -vp $(intdir); fi


.PHONY: clean
clean:
	$(rm) $(rmflags) $(target) $(objs)


.PHONY: build
build: all


.PHONY: rebuild
rebuild: clean all

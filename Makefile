CC = clang
# ?= means define if unset
CFLAGS ?= -Wall
#LDFLAGS # can be set in env to pass additional library paths
build_dir = out
debug_binary = $(build_dir)/debug
objects = main.o sed-pcre.o
sources = lib/main.c lib/src/sed-pcre.c
test_objects = foo.o
test_sources = tests/foo.c
test_binary = $(build_dir)/test
test_ld_libs = -lm -lrt -lpthread -lcheck -lsubunit
#test_ld_libs = -lcheck

$(debug_binary): lib/main.c $(build_dir) $(objects)
	@echo '> building debug app'
	$(CC) $(objects) -o $(debug_binary) $(LDFLAGS)

.PHONY: test
test: $(test_binary)
	@echo '> running tests'
	$(test_binary)

$(test_binary): $(objects) $(test_objects) $(build_dir)
	@echo '> building test app'
	$(CC) sed-pcre.o $(test_objects) -o $(test_binary) $(test_ld_libs) $(LDFLAGS)

$(test_objects): $(test_sources)
	@echo '> compiling test sources'
	$(CC) -c $(test_sources) $(CFLAGS)

$(objects): lib/main.c lib/src/sed-pcre.c
	@echo '> compiling source files'
	$(CC) -c $(sources) $(CFLAGS)

$(build_dir):
	@echo "> ensure out $$(build_dir) exists"
	mkdir -p $(build_dir)

.PHONY: clean
clean:
	rm -rf $(binary) $(build_dir) $(objects) $(test_objects)

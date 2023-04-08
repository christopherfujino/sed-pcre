CC = clang
CFLAGS = -Wall
build_dir = out
binary = $(build_dir)/main
objects = main.o sed-pcre.o
sources = lib/main.c lib/src/sed-pcre.c
test_objects = foo.o
test_sources = tests/foo.c
test_binary = $(build_dir)/test
test_ld_libs = -lm -lrt -lpthread -lcheck -lsubunit

debug: lib/main.c $(build_dir) $(objects)
	@echo '> building debug app'
	$(CC) $(objects) -o $(binary)

test: $(test_binary)
	@echo '> running tests'
	$(test_binary)

$(test_binary): $(objects) $(test_objects) $(build_dir)
	@echo '> building test app'
	$(CC) sed-pcre.o $(test_objects) -o $(test_binary) $(test_ld_libs)

$(test_objects): $(test_sources)
	@echo '> compiling test sources'
	$(CC) -c $(test_sources)

$(objects): lib/main.c lib/src/sed-pcre.c
	@echo '> compiling source files'
	$(CC) -c $(sources)

$(build_dir):
	@echo "> ensure out $$(build_dir) exists"
	mkdir -p $(build_dir)

clean:
	rm -rf $(binary) $(build_dir) $(objects)

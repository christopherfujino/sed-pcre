CC = clang
build_dir = out
binary = $(build_dir)/main

main: debug
	echo 'executing debug app'
	$(binary)

debug: main.c $(build_dir)
	echo 'building debug app'
	$(CC) main.c -o $(binary)

$(build_dir):
	echo "ensure out $$(build_dir) exists"
	mkdir -p $(build_dir)

clean:
	rm -rf $(binary) $(build_dir)

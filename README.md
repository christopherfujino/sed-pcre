# psed

Like `sed`, but with PCRE.

## Building

```bash
cd /path/to/sed-pcre
mkdir build
cd build
cmake ..
make
```

## Test Suite

[check](https://github.com/libcheck/check) is a dependency for running the
test suite.

```bash
sudo apt install check # on debian/ubuntu
sudo pacman -S check # on arch linux
```

### Running tests from vim

To run tests from vim, first ensure you have a successful build.

Then, from in vim/NeoVim with the project root as the working directory, run
`:make -C build/ test` in the command line. Then, you can see the results by
opening the quickfix list with `:copen`.

## Legal

This is not an official Google product.

#!/usr/bin/env bash

# add macports paths
export CFLAGS=-I/opt/local/include
export LDFLAGS=-L/opt/local/lib

set -x
exec make $@

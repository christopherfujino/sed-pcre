#!/usr/bin/env bash

set -euo pipefail

rm -rf build/
mkdir build
cd build/

ARGS=''

if type ninja >/dev/null; then
  echo 'found ninja'
  ARGS="$ARGS -GNinja"
fi

cmake .. $ARGS

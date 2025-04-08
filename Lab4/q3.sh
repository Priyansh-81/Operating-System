#!/bin/bash
# Usage: ./sortargs.sh arg1 arg2 arg3 ...

for arg in "$@"; do
  echo "$arg"
done | sort
#!/usr/bin/env sh
# This script is to be used on POSIX compatible shells.

# Format all header and source files using clang-format,
# with our custom LLVM-based formatting configuration.

clang-format -style=file:.clang-format -i $(git ls-files *.h *.c)

@echo off
REM This script is to be used on Command Prompt shells

REM Format all header and source files using clang-format,
REM with our custom LLVM-based formatting configuration.

for /f "delims=" %%i in ('git ls-files "*.h" "*.c"') do (
    clang-format -style=file:.clang-format -i "%%i"
)

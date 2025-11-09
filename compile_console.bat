@echo off
echo Compiling Advanced Dictionary System...
echo.

REM Change to project directory
cd /d "%~dp0"

REM Compile with GCC
gcc -Wall -O2 -o dictionary.exe main.c dictionary.c spellchecker.c heap.c

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ✅ Compilation successful!
    echo.
    echo Run with: dictionary.exe
) else (
    echo.
    echo ❌ Compilation failed!
    pause
)

@echo off
echo Compiling GUI Dictionary with GTK3...
echo.

REM Change to project directory
cd /d "%~dp0"

REM Use MSYS2 GCC with full command
C:\msys64\mingw64\bin\gcc.exe -Wall -O2 -o dictionary_gui.exe dictionary.c spellchecker.c heap.c autocomplete.c dictionary_gui.c -DLIBDEFLATE_DLL -IC:/msys64/mingw64/include/gtk-3.0 -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/pango-1.0 -IC:/msys64/mingw64/include/harfbuzz -IC:/msys64/mingw64/include/pango-1.0 -IC:/msys64/mingw64/include/fribidi -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/atk-1.0 -IC:/msys64/mingw64/include/cairo -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/freetype2 -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/harfbuzz -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/pixman-1 -IC:/msys64/mingw64/include/gdk-pixbuf-2.0 -IC:/msys64/mingw64/include/libpng16 -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/webp -IC:/msys64/mingw64/include -IC:/msys64/mingw64/include/glib-2.0 -IC:/msys64/mingw64/lib/glib-2.0/include -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib -lgtk-3 -lgdk-3 -lz -lgdi32 -limm32 -lshell32 -lole32 -luuid -lwinmm -ldwmapi -lsetupapi -lcfgmgr32 -lhid -lwinspool -lcomctl32 -lcomdlg32 -lpangowin32-1.0 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ✅ Compilation successful!
    echo.
    echo Run with: dictionary_gui.exe
) else (
    echo.
    echo ❌ Compilation failed!
    pause
)

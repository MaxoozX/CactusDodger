@echo off
set /p filename=Enter executable name:
echo Compiling as %filename%
g++ -LD:\Programmation\Extern\SDL2\SDL2-2.0.16\i686-w64-mingw32\lib -ID:\Programmation\Extern\SDL2\SDL2-2.0.16\i686-w64-mingw32\include Code/*.cpp -w "-Wl,-subsystem,windows" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o %filename%

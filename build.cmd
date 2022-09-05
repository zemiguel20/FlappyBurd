@echo off
set BUILD_FOLDER=.\build\windows
set RAYLIB_FOLDER=.\dependencies\raylib

if not exist %BUILD_FOLDER%\ mkdir %BUILD_FOLDER%

clang++ ^
source\*.cpp ^
source\Core\*.cpp ^
-Wall ^
-o %BUILD_FOLDER%\FlappyBurd.exe ^
-std=c++17 ^
-O3 ^
-I %RAYLIB_FOLDER%\include ^
-L %RAYLIB_FOLDER%\lib -l raylibdll.lib

Xcopy .\assets %BUILD_FOLDER%\assets\ /e /y
Xcopy %RAYLIB_FOLDER%\lib\raylib.dll %BUILD_FOLDER%\ /e /y
@echo off
set BUILD_FOLDER=.\build\windows
set RAYLIB_FOLDER=.\3rd\raylib

if not exist %BUILD_FOLDER%\ mkdir %BUILD_FOLDER%

clang++ "src\*.cpp" -Wall -o %BUILD_FOLDER%\FlappyBurd.exe -std=c++17 -I %RAYLIB_FOLDER%\include -L %RAYLIB_FOLDER%\lib -l raylibdll.lib

Xcopy .\res %BUILD_FOLDER%\res\ /e /y
Xcopy %RAYLIB_FOLDER%\lib\raylib.dll %BUILD_FOLDER%\ /e /y
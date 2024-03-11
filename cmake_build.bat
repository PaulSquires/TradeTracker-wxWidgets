@echo off

REM CONFIGURE
cmake -S. -Bbuild

REM BUILD
cmake --build build -j


@echo off

REM CONFIGURE
cmake -S. -Bbuild

REM BUILD
cmake --build build -j

REM RUN
IF %ERRORLEVEL% NEQ 0 (echo Build Failed!) ELSE (start .\build\Debug\TradeTracker.exe)


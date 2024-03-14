@ECHO off

REM This batch file must be in same folder as CMakeLists.txt


REM *************************
REM    CONFIGURE AND BUILD
REM *************************
CD %~dp0
SET build_dir=build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -S. -B%build_dir% 
cmake --build %build_dir% -j
IF %ERRORLEVEL% NEQ 0 (GOTO BUILD_FAILED) 


REM *************************
REM     RUN APPLICATION
REM *************************
IF "%~1"=="" exit 0
SET app_name=%~dp0%build_dir%\Debug\%1.exe
ECHO Run application: %app_name%
START %app_name%
EXIT 0


:BUILD_FAILED
ECHO Build Failed!
EXIT 1

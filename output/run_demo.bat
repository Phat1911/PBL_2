@echo off
echo Starting Qt6 Demo Application...
set PATH=C:\Qt\6.8.0\mingw_64\bin;C:\Qt\Tools\mingw1310_64\bin;C:\Qt\Tools\CMake_64\bin;C:\Qt\Tools\Ninja;%PATH%
start "" "%~dp0build\Qt6Demo.exe"

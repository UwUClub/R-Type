@echo off
call "C:\BuildTools\Common7\Tools\VsDevCmd.bat"
cmake -S . -B ./build
cmake --build ./build --config Release -j 8

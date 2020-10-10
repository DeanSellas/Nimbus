@echo off
title Generate Projects

IF not "%~1" == "VSCODE" (color b)

call vendor\bin\premake\premake5.exe vs2019
IF not "%~1" == "VSCODE" (pause)
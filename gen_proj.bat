@echo off
DEL t6zm_cheat.sln /Q
DEL t6zm_cheat\t6zm_cheat.vcxproj
DEL t6zm_cheat\t6zm_cheat.vcxproj.filters
DEL t6zm_cheat\t6zm_cheat.vcxproj.user

premake5 vs2019
IF %ERRORLEVEL% NEQ 0 (
  PAUSE
)
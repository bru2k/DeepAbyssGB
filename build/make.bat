:Compile
@echo off
..\..\..\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o main.o ..\main.c
..\..\..\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -o DeepAbyss.gb main.o
pause
cls
echo Recompile? [Y/N]
@echo off
choice /c yn /n
if %errorlevel%==1 goto Compile
if %errorlevel%==2 goto Quit

:Finished

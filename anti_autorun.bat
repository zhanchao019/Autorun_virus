
@echo off
setlocal ENABLEDELAYEDEXPANSION ENABLEEXTENSIONS
set /a n=0
set dl=CDEFGHIJKLMNOPQRSTUVWXYZ
:s
set d=!dl:~%n%,1!:
echo y|cacls %d%/autorun.inf /t /c /e /g everyone:f>nul 2>nul
del /f /q /a s h r a %d%/autorun.inf>nul 2>nul
for /f "delims=" %%a in ('dir /s /b /a s h r a %d%/autorun.inf') do (rd /s /q %%a./&rd /s /q %d%/autorun.inf)>nul 2>nul
set /a n=n+1 
if not %n%==24 goto s
pause

echo off
CALL ..\PathSET.BAT
CALL ..\TOOLS\BuildAll.BAT > build.log
if ERRORLEVEL 1 goto builderr
goto batchexit
:builderr
echo ############################
echo       Build Error!!
echo   Please Read "Build.Log"
echo ############################
pause
:batchexit

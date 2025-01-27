echo off
rem #####################################################
rem   CASIO PocketViewer Addin Program Build Batch File
rem     Copyright (c) 2002 by CASIO COMPUTER CO,.LTD
rem                 All Rights Reserved
rem #####################################################
rem ###############################
rem            clean
rem ###############################
if exist release\*.OBJ del release\*.OBJ
if exist release\*.RLD del release\*.RLD
if exist release\*.MAP del release\*.MAP
if exist debug\*.OBJ del debug\*.OBJ
if exist debug\*.MAP del debug\*.MAP
if exist user_bin\*.ABS del user_bin\*.ABS
if exist user_bin\*.DBG del user_bin\*.DBG
if exist user_bin\*.pva del user_bin\*.pva
if exist user_bin\fin del user_bin\fin
if exist user_bin\findbg del user_bin\findbg
if exist make\temp.mak del make\temp.mak
rem ###############################
rem          debug build
rem ###############################
genmake sources.def make\srcscp.mak
if errorlevel 1 goto dbgmakeerr
copy ..\shcdir.def+make\makedbg1.mak+sources.def+make\srcscp.mak+make\makedbg2.mak make\temp.mak
hmake make\temp.mak
echo _
echo ###############################
rem if errorlevel 1 goto dbgmakeerr
if exist user_bin\findbg goto dbgmakeok
:dbgmakeerr
echo       Debug Build Error.
seterr 1
goto batchexit
:dbgmakeok
echo    Debug Build Successful!
echo ###############################
seterr 0
rem ###############################
rem          release build
rem ###############################
copy ..\shcdir.def+make\make1.mak+sources.def+make\srcscp.mak+make\make2.mak make\temp.mak
hmake make\temp.mak
echo _
echo ###############################
rem if errorlevel 1 goto relmakeerr
if exist user_bin\fin goto relmakeok
echo     Release Build Error.
goto batchexit
:relmakeok
echo   Release Build Successful!
:batchexit
echo ###############################
echo _

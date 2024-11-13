
cls
cd ..

:-----------------------------------
rmdir BuildBinaryDebug /S /Q
mkdir BuildBinaryDebug
:-----------------------------------
cmake -S SourceCode -B BuildBinaryDebug -D CMAKE_CONFIGURATION_TYPES="Debug"
:===================================
rmdir BuildBinaryRelease /S /Q
mkdir BuildBinaryRelease
:-----------------------------------
cmake -S SourceCode -B BuildBinaryRelease -D CMAKE_CONFIGURATION_TYPES="Release"
:-----------------------------------

:运行结束后不退出CMD
@cmd.exe
cmd
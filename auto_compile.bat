set CMAKE_PREFIX_PATH=C:\Qt\Qt5.9.1\5.9.1\msvc2017_64
cmake -G"Visual Studio 15 2017 Win64" ../../
cmake --build . --config release 
cd C:\Users\%USERNAME%\Desktop\Projects\RpcRuler\Build\x64\bin\Release 
mkdir RpcView64
copy *.dll RpcView64\
copy *.exe RpcView64\
C:\Qt\Qt5.9.1\5.9.1\msvc2017_64\bin\windeployqt.exe --release RpcView64

set VCPKG_PATH="D:\works\vcpkg"

cmake -S. -Bbuild_vs -G"Visual Studio 16 2019" -A x64 -DBUILD_SHARED_LIBS=OFF ^
-DCMAKE_TOOLCHAIN_FILE=%VCPKG_PATH%\scripts\buildsystems\vcpkg.cmake ^
-DVCPKG_TARGET_TRIPLET=x64-windows-static -DOpenCV_DIR=D:\commonlib\opencv\opencv3416\build
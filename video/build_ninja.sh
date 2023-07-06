# build sdl
cmake -GNinja -Bbuild_ninja/sdl -DCMAKE_INSTALL_PREFIX=`pwd`/build_ninja/install 3rdparty/sdl
cmake --build build_ninja/sdl -j 10
cmake --install build_ninja/sdl

# build ffplayer
cmake -GNinja -Bbuild_ninja  -DCMAKE_INCLUDE_PATH=`pwd`/build_ninja/install/include \
  -DCMAKE_LIBRARY_PATH=`pwd`/build_ninja/install/lib .
cmake --build build_ninja
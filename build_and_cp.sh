cmake --build build_ninja
cmake --build network/build_android
adb push network/build_android/tcp_send_int_demo /data/local/tmp/
adb push network/build_android/tcp_send_struct_demo /data/local/tmp/
adb push network/build_android/tcp_send_struct_demo_1 /data/local/tmp/

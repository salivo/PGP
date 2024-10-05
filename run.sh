clear
typos

cmake build -B build -S . -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBUILD_SHARED_LIBS=ON -DUSE_EXTERNAL_GLFW=ON -DUSE_WAYLAND=ON
cmake --build build --config Release

case "$1" in
  "b")
    ;;

  "t")
        ctest --output-on-failure --test-dir build
    ;;
  *)
        cmake build -B build -S . -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBUILD_SHARED_LIBS=ON -DUSE_EXTERNAL_GLFW=ON -DUSE_WAYLAND=ON
        cmake --build build --config Release
        ./build/PGP
    ;;
esac

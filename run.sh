cmake build -B build -S . -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBUILD_SHARED_LIBS=ON -DUSE_EXTERNAL_GLFW=ON -DUSE_WAYLAND=ON 
cmake --build build --config Release 
./build/PGP                                                                                        

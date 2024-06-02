cmake build -B build -S . -DBUILD_SHARED_LIBS=ON -DUSE_EXTERNAL_GLFW=ON -DUSE_WAYLAND=ON
cmake --build build --config Release 
./build/PGP                                                                                        

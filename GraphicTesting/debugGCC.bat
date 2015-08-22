mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles" ../src
make
cd ..
clean.bat
One way of building is:
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
make -C build

And the run with
./build/main

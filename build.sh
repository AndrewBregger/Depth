# [! -d "./build" ] && mkdir build
pushd build
cmake ..
make -j8
popd
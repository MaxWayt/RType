rm -rf build
rm -rf rtype
mkdir build &&
mkdir rtype &&
cd build &&
cmake ../ -DCMAKE_INSTALL_PREFIX=../rtype -DDEBUG=1
cd -

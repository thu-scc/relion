
### install mpiP

1. install binutils

2. install mpiP

```sh
> wget https://jaist.dl.sourceforge.net/project/mpip/mpiP/mpiP-3.4.1/mpiP-3.4.1.tar.gz
> tar -xf mpiP-3.4.1.tar.gz
> cd mpiP-3.4.1
```

open `mpiPi.h.in` and change `char *av[32];` to `char *av[3200];` in line 163.

```sh
> ./configure --prefix=$HOME/install --with-include=-I$HOME/install/include --with-ldflags=-L$HOME/install/lib
> make
> make install
```

### install relion

```sh
export LIBRARY_PATH=$LIBRARY_PATH:/path/to/mpiP/
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=relwithdebinfo -DCUDA_ARCH=60 -DCMAKE_INSTALL_PREFIX=$HOME/install
make -j
make install
```

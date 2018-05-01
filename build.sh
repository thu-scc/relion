#!/bin/sh
rm -rf build
mkdir build
cd build
export CXX=icpc
export I_MPI_CXX=$CXX
export CC=icc
export I_MPI_CC=$CC
export OPT="-Ofast -xHost -fno-alias -align -qopt-report=5"
export CUOPT="-O3 -arch=sm_70"
cmake .. -DCUDA_ARCH=70 -DDoublePrec_GPU=OFF -DCudaTexture=ON -DCMAKE_INSTALL_PREFIX=/home/jiguanglizipao/.local/relion -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DFORCE_OWN_FFTW=ON -DCMAKE_CXX_FLAGS_RELEASE="$OPT" -DCMAKE_C_FLAGS_RELEASE="$OPT" -DCMAKE_EXE_LINKER_FLAGS_RELEASE="$OPT" -DRELION_NVCC_FLAGS_RELEASE="$CUOPT"
make install -j

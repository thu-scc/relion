rm -rf CMakeCache.txt CMakeFiles/ src/apps/CMakeFiles/ && CXX=icpc CC=icc I_MPI_CXX=icpc I_MPI_CC=icc cmake . -DBUILD_SHARED_LIBS=OFF -DCMAKE_EXE_LINKER_FLAGS_RELEASE="-ipo" -DCMAKE_CXX_FLAGS_RELEASE="-ipo" -DCMAKE_C_FLAGS_RELEASE="-ipo" -DRELION_FFTW_LIB=/usr/lib64/libfftw3.so && CXX=icpc CC=icc I_MPI_CXX=icpc I_MPI_CC=icc make -j
cp bin/relion_refine_mpi relion_cpu_fftw
rm -rf CMakeCache.txt CMakeFiles/ src/apps/CMakeFiles/ && CXX=icpc CC=icc I_MPI_CXX=icpc I_MPI_CC=icc cmake . -DBUILD_SHARED_LIBS=OFF -DCMAKE_EXE_LINKER_FLAGS_RELEASE="-ipo" -DCMAKE_CXX_FLAGS_RELEASE="-ipo" -DCMAKE_C_FLAGS_RELEASE="-ipo" -DRELION_FFTW_LIB=/usr/local/cuda-9.1/lib64/libcufftw.so && CXX=icpc CC=icc I_MPI_CXX=icpc I_MPI_CC=icc make -j
cp bin/relion_refine_mpi relion_gpu_fftw


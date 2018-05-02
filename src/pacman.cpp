#include "pacman.h"
#include "mpi.h"

int pacman::rank = 0;
int pacman::size = 0;

void pacman::init()
{
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
}


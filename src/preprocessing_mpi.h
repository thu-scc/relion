/***************************************************************************
 *
 * Author: "Sjors H.W. Scheres"
 * MRC Laboratory of Molecular Biology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * This complete copyright notice must be included in any revised version of the
 * source code. Additional authorship citations may be added, but existing
 * author citations must be preserved.
 ***************************************************************************/

#ifndef PREPROCESSING_MPI_H_
#define PREPROCESSING_MPI_H_
#include "src/mpi.h"
#include "src/preprocessing.h"
#include "src/parallel.h"

class PreprocessingMpi: public Preprocessing
{
private:
	MpiNode *node;

public:
	/** Destructor, calls MPI_Finalize */
    ~PreprocessingMpi()
    {
        delete node;
    }

    // Limit the number of effective MPI nodes to this value, rather than what is given through mpirun
    int max_mpi_nodes;

    /** Read
     * This could take care of mpi-parallelisation-dependent variables
     */
    void read(int argc, char **argv);

    // Parallelized run functions
    void runExtractParticles();
    void run();

};

#endif /* PREPROCESSING_MPI_H_ */
